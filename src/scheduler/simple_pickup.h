//
// Created by genshen on 6/30/18.
//

#ifndef PNOHS_SIMPLE_PICKUP_H
#define PNOHS_SIMPLE_PICKUP_H


#include <fmt/string.h>
#include "strategy_adapter.h"

class SimplePickup : public StrategyAdapter {
public:
    SimplePickup(SContext &context);

    SimulationNode *pickRunnable();

    static const std::string Key;

};


#endif //PNOHS_SIMPLE_PICKUP_H
