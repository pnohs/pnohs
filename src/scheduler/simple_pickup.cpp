//
// Created by genshen on 6/30/18.
//

#include "simple_pickup.h"

const std::string SimplePickup::Key = "simple";

SimplePickup::SimplePickup(SContext &context) : StrategyAdapter(context) {}

SimulationNode *SimplePickup::pickRunnable() {
    for (SimulationNode &sNode :*(context.pNodesPool->simulationNodes)) {
        if (sNode._time_steps < context._total_steps && sNode.upstream.isReady()) {
            return &sNode;
        }
    }
    return nullptr;

}
