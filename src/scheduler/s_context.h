//
// Created by genshen on 6/30/18.
//

#ifndef PNOHS_S_CONTEXT_H
#define PNOHS_S_CONTEXT_H

#include "../simulation_node.h"
#include "../nodes_pool.h"

/**
 * scheduler context.
 * The basic data for scheduling is placed here.
 * Including all simulation nodes, time-steps, and current simulation node.
 *
 */
class SContext {
public:

    // the total simulation time steps.
    const unsigned long _total_steps;

    // pointer of current simulation node.
    SimulationNode *curNode = nullptr;

    // it is not empty at runtime.
    NodesPool *pNodesPool; // all nodes

    /**
     *
     * @param total_steps total simulation steps.
     */
    SContext(unsigned long total_steps);

    ~SContext();
};


#endif //PNOHS_S_CONTEXT_H
