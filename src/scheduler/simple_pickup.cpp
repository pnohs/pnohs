//
// Created by genshen on 6/30/18.
//

#include "simple_pickup.h"

const std::string SimplePickup::Key = "simple";

SimplePickup::SimplePickup(SContext &context) : StrategyAdapter(context) {}

SimulationNode *SimplePickup::pickRunnable() {
    return nullptr; // todo
}
