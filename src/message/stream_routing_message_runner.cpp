//
// Created by genshen on 4/7/18.
//

#include "stream_routing_message_runner.h"

// initial context for thread here.
StreamRoutingMessageRunner::StreamRoutingMessageRunner(Context &ctx, NodesPool *pPool) : ctx(ctx), pNodesPool(pPool) {}

bool StreamRoutingMessageRunner::shouldDetach() const {
    return pNodesPool->potentiallyCompleted();
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
}
