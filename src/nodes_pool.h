//
// Created by genshen on 4/4/18.
//

#ifndef PNOHS_NODES_POOL_H
#define PNOHS_NODES_POOL_H

#include "simulation_node.h"

/**
 * NodePool is a collection of all simulation nodes on this processor.
 * {@see @var}
 */
class NodesPool {
public:

    friend class Scheduler;

    NodesPool();

    /**
     * add a simulation node to vector @var simulationNodes,
     */
    void appendNode(const SimulationNode &snode);

    /**
     * checkout whether there is a node whose id is the given id,
     * returns pointer of SimulationNode if found.
     * @param id node id
     * @return if true, return pointer of the SimulationNode, otherwise return nullptr.
     */
    SimulationNode *findNodeById(const _type_node_id node_id);

    /**
     * Deliver simulation to its downstream node.
     * If it is the outlet of the river, write simulation result only.
     * Otherwise, deliver result to its downstream.
     * In this case, if the downstream is on this processor, just copy result to corresponding task queue.
     * Otherwise, send result to the downstream on other processor by communicating.
     * @param node_id the target simulation node id.
     */
    void deliver(SimulationNode &current_node);

private:

    /**
     * all nodes on this processor.
     */
    std::vector<SimulationNode> simulationNodes;

    /**
     * Deliver simulation result to node on the same processor directly.
     * @param node_id the target simulation node id.
     */
    void straightforwardDeliver(const _type_node_id node_id);

};


#endif //PNOHS_NODES_POOL_H
