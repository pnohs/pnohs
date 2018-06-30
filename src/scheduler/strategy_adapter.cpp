//
// Created by genshen on 6/30/18.
//

#include "strategy_adapter.h"

StrategyAdapter::StrategyAdapter(SContext &context) : context(context) {
}

void StrategyAdapter::onStrategySelected() {
    nodesIter = context.pNodesPool->simulationNodes->begin(); // initialize nodesIter.
}
