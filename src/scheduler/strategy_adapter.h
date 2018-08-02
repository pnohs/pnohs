//
// Created by genshen on 6/30/18.
//

#ifndef PNOHS_STRATEGY_ADAPTER_H
#define PNOHS_STRATEGY_ADAPTER_H

#include "s_context.h"

/**
 * In this class, it includes the interface of implementation of node pickup strategy.
 * Each different pickup strategy must implement the virtual methods in this class and register to scheduler.
 */
class StrategyAdapter {
public:

    StrategyAdapter(SContext &context);

    virtual ~StrategyAdapter();

    /**
     * select an runnable node (its all upstream task queue are not empty).
     * @return  returns an simulation node if there is at least node fit the condition, otherwise returns nullptr.
     */
    virtual SimulationNode *pickRunnable() = 0;

    /**
     * If corresponding strategy is selected to use,
     * then this method will be called to initialize the corresponding strategy entity.
     * Note that, this method should be called after all simulation nodes are added to NodesPoll (in context).
     */
    virtual void onStrategySelected();

protected:
    /**
     * iterator of std::list, which is used in schedule select strategy.
     * The iterator will initialized as the first element of nodes list.
     * It points to {@var curNode}.
     */
    SimulationNodesSet::iterator nodesIter;

    // context of scheduling
    SContext &context;

};


#endif //PNOHS_STRATEGY_ADAPTER_H
