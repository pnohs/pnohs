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
    void deliver(SimulationNode *current_node);

    /**
     * check the status of potential tasks.
     * If we don't need any more routing results from upstream nodes for any node,
     * we can still finish the whole simulation on those node, true will be returned.
     * If some node(s) have to wait the routing results from upstream node(s) in later time, false will be returned.
     *
     * In other words, for all nodes, if the data in task queue is enough to finish the whole simulation
     * (no more data from upstream nodes), this status is called potentially completed.
     * @return False for some node(s) have to wait the routing results(task) from its/their upstream node(s) soon after. True for otherwise.
     */
    bool potentiallyCompleted();

    /**
     * Check if all nodes on this processor has completed their simulation.
     * In fact, just check if each simulation nodes has reached its totalSteps.
     * @return true for all simulation finished (the whole simulation will end later), false for otherwise.
     */
    bool allCompleted();

    /**
     * After finishing the simulation of each time step of each node,
     * this function will be called to update some status variable.
     * @param total_steps
     */
    void updateStatus(const unsigned long total_steps);

private:

    bool status_all_tasks_completed = false, status_tasks_potentially_completed = false;

    /**
     * all nodes on this processor.
     */
    std::vector<SimulationNode> simulationNodes;

    /**
     * Deliver simulation result to node on the same processor directly.
     * @param current_node_id the target simulation node id.
     * @param downstream_node_id // todo document
     */
    void straightforwardDeliver(_type_node_id current_node_id, _type_node_id downstream_node_id);

    /**
     * deliver stream routing data to the downstream node on the remote processor.
     * @param current_node_id // todo document
     * @param downstream_node
     */
    void remoteDeliver(_type_node_id current_node_id,const DownstreamNode &downstream_node);
};


#endif //PNOHS_NODES_POOL_H
