//
// Created by genshen on 4/4/18.
//

#include <utils/mpi_utils.h>
#include "nodes_pool.h"
#include "utils/sim_domain.h"
#include "adapter/type_routing.h"

NodesPool::NodesPool() {
    simulationNodes = new SimulationNodesSet();
}

NodesPool::~NodesPool() {
    simulationNodes->clear(); // todo release memory.
}

void NodesPool::appendNode(const SimulationNode &snode) { // todo remove all nodes.
    // todo checkout node id not null.
    simulationNodes->push_back(snode);
}

_type_nodes_count NodesPool::nodes() const {
    return simulationNodes->size();
}

SimulationNode *NodesPool::findNodeById(const _type_node_id node_id) {
    // travel all simulation nodes to find a node.
    for (SimulationNode &node:*simulationNodes) {
        if (node.id == node_id) {
            return &node;
        }
    }
    return nullptr;
}

void NodesPool::toPureGraph(Graph *graph) {
    for (SimulationNode &snode: *simulationNodes) {
        graph->addNode(snode);
    }
}

void NodesPool::deliver(const SimulationNode &current_node) {
    if (current_node.isRiverOutlet()) {
        // if its outlet of this river
        current_node.outletReached();
    } else {
        // if its downstream is on this processor, just do data copy in memory.
        if (domain::mpi_sim_process.own_rank == current_node.downstream.nodes[0].location) {
            straightforwardDeliver(current_node);
        } else {
            remoteDeliver(current_node); // deliver to the node on other processor.
        }
    }
}

void NodesPool::remoteDeliver(const SimulationNode &current_node) {
    const DownstreamNode &downstream_node = current_node.downstream.nodes[0];
    TypeRouting data = current_node.constructRouting();
    MPI_Send(&data, sizeof(TypeRouting), MPI_BYTE,
             downstream_node.location, TagStreamRoutingMessage, domain::mpi_sim_process.comm);
}

// todo usr event message.
void NodesPool::straightforwardDeliver(const SimulationNode &current_node) {
    _type_node_id downstream_node_id = current_node.downstream.nodes[0].id;
    SimulationNode *downstreamNode = findNodeById(downstream_node_id);
    if (downstreamNode != nullptr) {
        // append routing results to upstream task list directly.
        TypeRouting data = current_node.constructRouting();
        bool append_status = downstreamNode->upstream.appendUpstreamRouting(current_node.id, data);
        // New task will be append to the task queue, but there is no need to wake up the blocked main thread.
        // because the main thread is running here.
        if (!append_status) {
            // todo log warning.
        } else {
//            updatePotentiallyCompletedStatus(); // todo
        }
    } else {
        // todo fault error, downstream not found on processor xxx.
    }
}

bool NodesPool::allCompleted() {
    return status_all_tasks_completed;
}

// update variable @var status_tasks_potentially_completed and @var status_all_tasks_completed.
void NodesPool::updateStatusAllCompleted(const unsigned long total_steps) {
    bool finish_status = true;
    // update status_all_tasks_completed
    for (SimulationNode &sNode : *simulationNodes) {
        if (sNode._time_step < total_steps) { // the node does not finish its simulation.
            finish_status = false;
            break;
        }
    }
    status_all_tasks_completed = finish_status;
}

void NodesPool::clearStatus() {
    status_all_tasks_completed = false;
}
