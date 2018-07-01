//
// Created by genshen on 6/30/18.
//

#include "ring_pickup.h"

const std::string RingPickup::Key = "ring";

RingPickup::RingPickup(SContext &context) : StrategyAdapter(context) {
}

SimulationNode *RingPickup::pickRunnable() {
    SimulationNodesSet::iterator itr_end = std::next(nodesIter, 1);
    SimulationNodesSet::iterator itr = itr_end;
    do { // travel the whole list to find a simulation node.
        if (itr == context.pNodesPool->simulationNodes->end()) {
            // if it is the past-the-end element
            // (which is the theoretical element that would follow the last element), pass it.
            itr++;
        }
        if (itr->_time_steps < context._total_steps && itr->upstream.isReady()) {
            nodesIter = itr;
            return &(*itr);
        }
        itr++;
    } while (itr != itr_end);

    return nullptr;
}
