//
// Created by genshen on 7/3/18.
//

#ifndef PNOHS_LONGEST_PICKUP_H
#define PNOHS_LONGEST_PICKUP_H

#include "strategy_adapter.h"
#include "ring_pickup.h"

/**
 *
 */
class LongestPickup : public StrategyAdapter {
public:
    explicit LongestPickup(SContext &context);

    ~LongestPickup() override;

    /**
     * the main implementation of Longest pickup strategy.
     * In this strategy, it will search the whole nodes list,
     * and return a node whose upstream queue is the longest in all ready nodes.
     *
     * "upstream queue is the longest" means:
     * we will compute the max size of queues of each node,
     * and then we will find the max value of max queue size.
     *
     * For example, we have 3 nodes, each node have 3 upstream, the queue size are list below:
     *
     * upstream queue size: |_3_|_2_|_4_|  |_4_|_0_|_8_|   |_1_|_4_|_6_|
     *
     *      nodes:            node 1          node 2           node3
     * Then the max size of queues of each node will be:
     * node1: 4, node 2: 8, node3: 6
     * At last, it will return a node with max value of max queue size in all ready nodes.
     * In this example, node 3 will be returned (node 2 is node ready).
     *
     * Note: the returned node must be ready, which means all task queue of this node are not empty
     * or the node is the river origin.
     * @return the picked node if found one which satisfy the rules, or null if all nodes are not ready.
     */
    SimulationNode *pickRunnable() override;

    static const std::string Key;
    static const int NO_NODE_PICKED = -1;
};

#endif //PNOHS_LONGEST_PICKUP_H
