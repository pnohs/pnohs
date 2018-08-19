//
// Created by genshen on 4/4/18.
//

#ifndef PNOHS_NODES_POOL_H
#define PNOHS_NODES_POOL_H

#include <functional>

#include "simulation_node.h"
#include "sys_context.h"
#include "message/stream_routing_message_runner.h"
#include "graph/graph.h"

/**
 * NodePool is a collection of all simulation nodes on this processor.
 * {@see @var}
 */
typedef std::list<SimulationNode> SimulationNodesSet;

class NodesPool {
public:

    /**
     * all nodes on this processor.
     */
    SimulationNodesSet *simulationNodes;

    NodesPool();

    // remove all simulation nodes.
    ~NodesPool();

    /**
     * add a simulation node to vector @var simulationNodes,
     */
    void appendNode(const SimulationNode &snode);

    /**
     * get the count of nodes on this processor.
     * @return the count of simulation nodes
     */
    _type_nodes_count nodes() const;

    /**
     * checkout whether there is a node whose id is the given id,
     * returns pointer of SimulationNode if found.
     * @param id node id
     * @return if true, return pointer of the SimulationNode, otherwise return nullptr.
     */
    SimulationNode *findNodeById(const _type_node_id node_id);

    /**
     * iterate all simulation node in this nodes pool.
     * for each node, the callback function will be called with passing the reference of this node.
     */
    template<typename Callable>
    inline void forEachNode(Callable callback) {
        for (SimulationNode &snode: *simulationNodes) {
            if (callback(snode)) {
                break;
            }
        }
    }

    /**
     * convert simulation nodes list to pure graph (which is nodes list. {@see graph/graph.h and graph/node.h })
     * In fact, it is just coping simulation nodes list to pure graph nodes.
     * @param graph pointer to a empty pure graph (without simulation information).
     */
    void toPureGraph(Graph *graph);

    /**
     * Deliver simulation to its downstream node.
     * If it is the outlet of the river, write simulation result only.
     * Otherwise, deliver result to its downstream.
     * In this case, if the downstream is on this processor, just copy result to corresponding task queue.
     * Otherwise, send result to the downstream on other processor by communicating.
     * @param current_node reference of current simulation node.
     */
    void deliver(const SimulationNode &current_node);

    /**
     * Return status of whether all tasks is potentially completed.
     * For all nodes, if we don't need any more routing results from upstream nodes,
     * we can still finish the whole simulation on those node, true will be returned.
     *
     * @return If some node(s) have to wait the routing results from upstream node(s) in later time, false will be returned. True for otherwise.
     */
//    bool potentiallyCompleted();

    /**
     * Return status of if all nodes has completed their simulation.
     * @return true for all simulation finished (the whole simulation will end later), false for otherwise.
     */
    bool allCompleted();

    /**
     * After finishing the simulation of each time step of each node,
     * this function will be called to update some status flag of {@var status_all_tasks_completed}.
     * In fact, just check if each simulation nodes has reached its totalSteps.
     * @param total_steps the total time steps of whole simulation.
     */
    void updateStatusAllCompleted(const unsigned long total_steps);

    /**
     * reset @var status_all_tasks_completed to initial value.
     */
    void clearStatus();

private:

    /**
     * Status of whether all nodes on this processor has finished all their simulation.
     */
    bool status_all_tasks_completed = false;

    /**
     * Deliver simulation result to node on the same processor directly.
     * just do memory copy.
     * @param current_node the current simulation node.
     */
    void straightforwardDeliver(const SimulationNode &current_node);

    /**
     * deliver stream routing data to the downstream node on the remote processor.
     * @param current_node the current simulation node.
     */
    void remoteDeliver(const SimulationNode &current_node);
};


#endif //PNOHS_NODES_POOL_H
