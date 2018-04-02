//
// Created by genshen on 3/27/18.
//

#include "simulation_node.h"

void SimulationNode::deliver() {
    if (this->downstream.isOutlet()) {
        // todo out put to letout
    } else {
        _type_graph_node_id streamId = this->downstream.downstreamNodes[0].id; // todo
    }
}

void SimulationNode::runoff() {

}

void SimulationNode::riverRouting() {

}
