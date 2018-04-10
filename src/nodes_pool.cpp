//
// Created by genshen on 4/4/18.
//

#include <utils/mpi_utils.h>
#include "nodes_pool.h"
#include "routing/type_routing.h"

NodesPool::NodesPool() : simulationNodes() {}

void NodesPool::appendNode(const SimulationNode &snode) { // todo remove all nodes.
    simulationNodes.push_back(snode);
}

SimulationNode *NodesPool::findNodeById(const _type_node_id node_id) {
    // travel all simulation nodes to find a node.
    for (SimulationNode &node:simulationNodes) {
        if (node.id == node_id) {
            return &node;
        }
    }
    return nullptr;
}

void NodesPool::deliver(SimulationNode *current_node) {
    if (current_node->isRiverOutlet()) {
        // if its outlet of this river.
        // todo out put to letout
    } else {
        // if its downstream is on this processor, just do data copy in memory.
        if (kiwi::mpiUtils::ownRank == current_node->downstream.nodes[0].location) {
            straightforwardDeliver(current_node->id, current_node->downstream.nodes[0].id);
        } else {
            remoteDeliver(current_node->id,
                          current_node->downstream.nodes[0]); // deliver to the node on other processor.
        }
    }
}

void NodesPool::remoteDeliver(_type_node_id current_node_id, const DownstreamNode &downstream_node) {
    TypeRouting data = TypeRouting(); // todo example
    data.routing_data = 3.14;
    data.source_id = current_node_id;
    data.destination_id = downstream_node.id;

    MPI_Send(&data, sizeof(TypeRouting), MPI_BYTE,
             downstream_node.location, TagStreamRoutingMessage, MPI_COMM_WORLD);
}

void NodesPool::straightforwardDeliver(_type_node_id current_node_id, _type_node_id downstream_node_id) {
    SimulationNode *downstreamNode = findNodeById(downstream_node_id);
    if (downstreamNode != nullptr) {
        // append routing results to upstream task list directly.
        TypeRouting data = TypeRouting(); // todo just an example;
        data.routing_data = 3.14;
        data.source_id = current_node_id;
        data.destination_id = downstream_node_id;
        bool append_status = downstreamNode->upstream.appendUpstreamRouting(current_node_id, data);
        // New task is append to the task queue, but there is no need to wake up the blocked main thread.
        // because the main thread is running here.
        if (!append_status) {
            // todo log warning.
        }
    } else {
        // todo fault error, downstream not found on processor xxx.
    }
}

bool NodesPool::potentiallyCompleted() {
    return status_tasks_potentially_completed;
}

bool NodesPool::allCompleted() {
    return status_all_tasks_completed;
}

// update variable @var status_tasks_potentially_completed and @var status_all_tasks_completed.
void NodesPool::updateStatus(const unsigned long total_steps) {
    bool finish_status = true;
    // update status_all_tasks_completed
    for (SimulationNode &sNode : simulationNodes) {
        if (sNode._time_steps < total_steps) { // the node does not finish its simulation.
            finish_status = false;
            break;
        }
    }
    status_all_tasks_completed = finish_status;

    bool potential_status = true;
    // update status_tasks_potentially_completed.
    for (SimulationNode &sNode : simulationNodes) {
        // nodes completed plus routing data in task queue.
        if (sNode._time_steps + sNode.upstream.minQueSize() < total_steps) {
            potential_status = false;
            break;
        }
    }
    status_tasks_potentially_completed = potential_status;
}
