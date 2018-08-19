//
// Created by genshen on 8/16/18.
//

#ifndef PNOHS_GRAPH_H
#define PNOHS_GRAPH_H

#include "node.h"

/**
 * The graph of simulation nodes.
 * Just the collection of all nodes(without simulation information) on this processor
 * with upstream and downstream relationship.
 *
 * @note the nodes on this processor are not the whole graph, they are just a part of graph,
 * all nodes in simulation domain with their relationship consists of the whole graph.
 * We call it "sub-graph".
 */
class Graph {
    friend class Traversing;

public:

    /**
     * add a node to sub-graph stored in {@var nodes}.
     * @param node reference of Node, the node to be added.
     */
    void addNode(Node &node);

    /**
     * It returns the count of nodes on this processor.
     * @return the count of nodes of sub-graph.
     */
    inline _type_nodes_count nodesCount() const {
        return nodes.size();
    }

    /**
     * It returns the nodes count of sub-graph on each processor in simulation domain.
     * The return data are stored in array @var counts,
     * the ith element in array stores the nodes count of sub-graph on ith processor.
     *
     * @note simulation domain: {@see domain::mpi_sim_process in utils/sim_domain.h},
     * which equals to domain::mpi_sim_process.all_ranks.
     *
     * @note The implementation of this method will involve global MPI communication,
     * which may effect program performance.
     *
     * @param counts array to store nodes count,
     * the length of this array must equal to the ranks in simulation domain.
     * And note that the array must be allocated before calling this method.
     */
    void globalNodesCount(_type_nodes_count *counts);

    /**
     * This function returns all nodes ids of sub-graph on this processor.
     * The ids are stored in array @var ids,
     * whose length must be at least the nodes count of sub-graph on this processor.
     * @param ids the ids of sub-graph on this processor are stored in this array.
     */
    void getGraphNodesIds(_type_node_id *ids);

    /**
     * The same as above, but returns std::vector.
     * @return the ids of sub-graph on this processor.
     */
    std::vector<_type_node_id> getGraphNodesIds();

private:

    /**
     * all nodes (without simulation information) in this processor and
     * their relationship will be saved here.
     * Their relationship means the upstream and downstream relationship of the nodes on this processor.
     * Note that the upstream and downstream nodes may located on other processors.
     */
    std::list<Node> nodes; // todo use pointer, returned by NodesPool.
};


#endif //PNOHS_GRAPH_H
