//
// Created by genshen on 7/3/18.
//

#include "longest_pickup.h"

const std::string LongestPickup::Key = "longest";

LongestPickup::LongestPickup(SContext &context) : StrategyAdapter(context) {}

LongestPickup::~LongestPickup() {

}

SimulationNode *LongestPickup::pickRunnable() {
    // @assert todo nedesIter notnull
    SimulationNodesSet::iterator itr_end = std::next(nodesIter, 1);
    SimulationNodesSet::iterator itr = itr_end;
    SimulationNodesSet::iterator itr_max_len;

    int queue_length_max = NO_NODE_PICKED;
    // travel the whole list to find a simulation node who has the longest upstream queue length.
    do {
        if (itr == context.pNodesPool->simulationNodes->end()) {
            // if it is the past-the-end element
            // (which is the theoretical element that would follow the last element), pass it.
            itr++;
        }
        // if this node is ok (it does not finish simulation, and its upstream is ready).
        if (itr->_time_step < context._total_steps && itr->upstream.isReady()) {
            // if this node is the river origin, {@variable len} can be 0.
            int len = static_cast<int>(itr->upstream.maxQueSize());
            // found a node whose upstream queue length is bigger than the preview ones.
            // Then. we set current node as the longest one.
            if (len > queue_length_max) {
                itr_max_len = itr;
                queue_length_max = len;
            }
        }
        itr++;
    } while (itr != itr_end);

    // if we have found a node, just return it.
    if (queue_length_max > NO_NODE_PICKED) {
        nodesIter = itr_max_len;
        return &(*itr_max_len);
    }
    return nullptr;
}

