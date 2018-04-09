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
            _type_node_id stream_id = current_node->downstream.nodes[0].id; // todo mpi communication.
        }
    }
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

bool NodesPool::hasMoreUnreachedTasks() {
    return status_has_more_unreached_tasks;
}

bool NodesPool::allFinished() {
    return status_all_tasks_finished;
}

// update variable @var status_has_more_unreached_tasks and @var status_all_tasks_finished.
void NodesPool::updateStatus(const unsigned long total_steps) {
    bool status = true;
    for (SimulationNode &sNode : simulationNodes) {
        if (sNode._time_steps <= total_steps) {
            status = false;
        }
    }
    status_all_tasks_finished = status;

    status = true;
    // todo update status_has_more_unreached_tasks.
    for (SimulationNode &sNode : simulationNodes) {
//        for(each upstream node of sNode){
//        if (sNode._time_steps+sNode.taskCount() <= total_steps) {
//            status = false;
//        }
//    }
    }
}
