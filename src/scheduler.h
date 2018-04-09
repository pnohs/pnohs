//
// Created by genshen on 4/9/18.
//

#ifndef PNOHS_SCHEDULER_H
#define PNOHS_SCHEDULER_H

#include "nodes_pool.h"
#include "context.h"

/**
 * In Scheduler, it includes the implementation of node selecting strategy,
 * stream routing strategy.
 */
class Scheduler {
public:
    SimulationNode *curNode = nullptr;

    // it is not empty at runtime.
    NodesPool *nodesPool; // all nodes

    /**
     * new scheduler with context and total simulation steps.
     * @param ctx context.
     * @param total_steps total simulation steps.
     */
    Scheduler(Context &ctx, unsigned long total_steps);

    ~Scheduler(); // remove all nodes in nodesPool.

    /**
     * select method pick one node that can run (this node didn't finish simulation, and its all upstream is ready).
     * If there is no node available, the thread will get blocked, until there is at least one node available.
     * @return true for no more available node
     */
    bool select();

private:
    const unsigned long _total_steps;

    Context &ctx;

    /**
    * select an runnable node (its all upstream task queue are not empty).
    * @param argTotalSteps the total simulation time steps.
    * @return  returns an simulation node if there is at least node fit the condition, otherwise returns nullptr.
    */
    SimulationNode *pickRunnable();

    /**
     * check if all nodes on this processor has finished their simulation.
     * In fact, just check if all simulation nodes have reached its totalSteps.
     * @return
     */
    bool allFinished();

};


#endif //PNOHS_SCHEDULER_H
