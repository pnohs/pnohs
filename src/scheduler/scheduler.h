//
// Created by genshen on 4/9/18.
//

#ifndef PNOHS_SCHEDULER_H
#define PNOHS_SCHEDULER_H

#include "s_context.h"
#include "strategy_adapter.h"

/**
 * In Scheduler, it runs schedule algorithm to pick up one runnable simulation node.
 * If there is no available node, the current thread is blocked util there is it an available node.
 * After getting an available node, the upstream data of this node can be obtained from queue.
 *
 * Note that, the node pick up strategies is not implemented in this class,
 * in this class, it just run pick up strategy and return an available simulation node.
 */
class Scheduler {
public:

    /**
     * new scheduler with context and total simulation steps.
     * @param ctx reference of system context.
     * @param scheduleContext reference of schedule context (nodes poll is in here.)
     */
    Scheduler(SysContext &ctx, SContext &scheduleContext);

    ~Scheduler(); // remove all nodes in pNodesPool.

    /**
     * set this pickup strategy to use.
     * may error: key not matching.
     * @param key the key to uniquely identifies the pickup strategy.
     * @return if the key exists in strategy container({@see StrategyContainer}), true will be returned,
     * otherwise false will be returned.
     */
    bool setPickupStrategy(const std::string &key);

    /**
     * select method pick one node that can run (this node didn't finish simulation, and its all upstream is ready).
     * If there is no node available, the thread will get blocked, until there is at least one node available.
     * @return true for no more available node
     */
    bool select();

    /**
     * this method will be called after each simulation time step finishing.
     */
    void postStep();

private:

    SysContext &ctx; // pointer of system context
    SContext &schCtx; // pointer of schedule context
    StrategyAdapter *pickup; // an pickup strategy.
};


#endif //PNOHS_SCHEDULER_H
