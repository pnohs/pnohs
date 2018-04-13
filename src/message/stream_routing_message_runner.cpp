//
// Created by genshen on 4/7/18.
//

#include "stream_routing_message_runner.h"
#include "../simulation_node.h"
#include "../nodes_pool.h"

// initial context for thread here.
StreamRoutingMessageRunner::StreamRoutingMessageRunner(Context &ctx, NodesPool *pPool, const unsigned long totalSteps) :
        total_steps(totalSteps), _msg_upper_bound(0), _msg_accumulator(0),
        ctx(ctx), pNodesPool(pPool) {}

void StreamRoutingMessageRunner::onAttach() {
    // initialize _msg_upper_bound here
    for (SimulationNode &sNode : pNodesPool->simulationNodes) {
        // exclude the nodes which is the origin of river.
        if (sNode.isRiverOrigin()) {
            continue;
        }
        for (UpstreamNode &upnode:sNode.upstream.nodes) {
            // exclude the upstream nodes which is located on the this processor.
            if (upnode.location == kiwi::mpiUtils::ownRank) {
                continue;
            }
            _msg_upper_bound++;
        }
    }
    _msg_upper_bound *= total_steps; // each task queue of upstream node will receive {@var total_steps} messages.
}

bool StreamRoutingMessageRunner::shouldDetach() const {
    return _msg_accumulator >= _msg_upper_bound;
}

bool StreamRoutingMessageRunner::filter(MPI_Status *pStatus) {
    return pStatus->MPI_TAG == TagStreamRoutingMessage; // only receive stream routing message.
}

void StreamRoutingMessageRunner::onMessage(MPI_Status *pStatus) {
    // receive upstream routing message/data.
    TypeRouting up_routing;
    MPI_Recv(&up_routing, sizeof(TypeRouting), MPI_BYTE, pStatus->MPI_SOURCE,
             TagStreamRoutingMessage, MPI_COMM_WORLD, MPI_STATUS_IGNORE); // todo use type: TypeRouting
    SimulationNode *pNode = pNodesPool->findNodeById(up_routing.destination_id);
    pNode->upstream.appendUpstreamRouting(up_routing.source_id, up_routing); // write queue.

    // wake up the blocked main thread if necessary.
    pthread_mutex_lock(&(ctx._t_mu));
    if (ctx._t_waiting) {
        // pthread_cond_signal() will have no effect if there are no threads currently blocked on cond.
        pthread_cond_signal(&(ctx._t_cond));
    }
    pthread_mutex_unlock(&(ctx._t_mu));
    _msg_accumulator++;
}

void StreamRoutingMessageRunner::onDetach() {}
