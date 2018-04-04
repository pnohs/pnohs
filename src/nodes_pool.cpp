//
// Created by genshen on 4/4/18.
//

#include <utils/mpi_utils.h>
#include "nodes_pool.h"


NodesPool::NodesPool(const unsigned long totalSteps) : totalSteps(totalSteps), simulationNodes() {}

void NodesPool::addNode(const SimulationNode &snode) {
    simulationNodes.push_back(snode);
}

// todo milestone: better pick strategy.
SimulationNode *NodesPool::pickRunnable() {
    for (SimulationNode &sNode : simulationNodes) {
        if (sNode._time_steps <= totalSteps && sNode.upstream.isReady()) {
            return &sNode;
        }
    }
    return nullptr;
}

bool NodesPool::allFinished() {
    for (SimulationNode &sNode : simulationNodes) {
        if (sNode._time_steps <= totalSteps) {
            return false;
        }
    }
    return true;
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

void NodesPool::deliver(SimulationNode &current_node) {
    if (current_node.isRiverOutlet()) {
        // if its outlet of this river.
        // todo out put to letout
    } else {
        // if its downstream is on this processor, just do data copy in memory.
        if (kiwi::mpiUtils::ownRank == current_node.downstream.nodes[0].location) {
            straightforwardDeliver(current_node.downstream.nodes[0].id);
        } else {
            _type_node_id streamId = current_node.downstream.nodes[0].id; // todo mpi communication.
        }
    }
}

void NodesPool::straightforwardDeliver(const _type_node_id node_id) {
    if (findNodeById(node_id) != nullptr) {

    } else {
        // todo fault error, downstream not found on processor xxx.
    }
}
