//
// Created by genshen on 6/30/18.
//

#ifndef PNOHS_RING_PICKUP_H
#define PNOHS_RING_PICKUP_H

#include "strategy_adapter.h"

/**
 * ring pickup strategy.
 */
class RingPickup : public StrategyAdapter {
public:
    RingPickup(SContext &context);

    SimulationNode *pickRunnable();

    static const std::string Key;
};


#endif //PNOHS_RING_PICKUP_H
