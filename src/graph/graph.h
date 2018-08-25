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
     * For all processor in simulation domain,
     * it returns the nodes count of sub-graph on each processor in simulation domain.
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
     * Similar as preview one, but it only for root processor (just like MPI_Gather and MPI_AllGather):
     * It returns the nodes count of sub-graph on each processor in simulation domain for root processor.
     * The other processors will be ignored.
     * 
     * @param counts array to store nodes count. only necessary for root processor.
     * can set it to null for non-root processor.
     * @param root the rank id for root processor.
     */
    void globalNodesCount(_type_nodes_count *counts, const kiwi::RID root);

    /**
     * get the total nodes count in simulation domain.
     * This function should be call by all processor at the same time.
     * Communication will be involved in this function.
     * @return total nodes count in simulation domain.
     */
//    _type_nodes_count globalNodesCount();

    /**
     * This function returns all nodes ids of sub-graph on this processor.
     * The ids are stored in array @var ids,
     * whose length must be at least the nodes count of sub-graph on this processor.
     * @param ids the ids of sub-graph on this processor are stored in this array.
     */
    void getLocalGraphNodesIds(_type_node_id *ids);

    /**
     * The same as above, but returns std::vector.
     * @return the ids of sub-graph on this processor.
     */
    std::vector<_type_node_id> getLocalGraphNodesIds();

    /**
     * This function gather all nodes ids in global graph for all processors in simulation domain.
     * The nodes ids are saved in array {@var ids}.
     *
     * @note before calling this function, you must known the nodes count on each processor.
     * Then, the length of array @var ids must be the sum of all nodes count on each processor.
     *
     * After calling this function, the array @var ids on the all processors
     * will be filled with all nodes ids of global graph.
     *
     * @param ids global graph nodes ids will be saved in this array.
     * the length of array @var ids must be the sum of all nodes count on each processor.
     * @param counts the nodes count of sub-graph on each processor.
     * the length of array @var counts must equal to the MPI ranks in simulation domain.
     */
    void gatherNodesIds(_type_node_id *ids, _type_nodes_count *counts);

    /**
     * Similar as preview one, but it one set global nodes ids for root processor.
     *
     * After calling this function, the array @var ids on the ROOT processor
     * will be filled with all nodes ids of global graph;
     * the array @var ids on the other processors will be ignored
     * (@var ids and @var counts can be null for non-root processors in this case).
     *
     * @param ids global graph nodes ids will be saved in this array.
     * the length of array @var ids must be the sum of all nodes count on each processor.
     * @param counts the nodes count of sub-graph on each processor.
     * the length of array @var counts must equal to the MPI ranks in simulation domain.
     * @param root the rank id for root processor.
     */
    void gatherNodesIds(_type_node_id *ids, _type_nodes_count *counts, const kiwi::RID root);

private:

    /**
     * all nodes (without simulation information) in this processor and
     * their relationship will be saved here.
     * Their relationship means the upstream and downstream relationship of the nodes on this processor.
     * Note that the upstream and downstream nodes may located on other processors.
     */
    std::list<Node> nodes; // todo use pointer, returned by NodesPool.

    /**
     * flags used for gathering graph nodes ids.
     */
    static const int FLAG_ROOT_ONLY = 0x100; // gather to root
    static const int FLAG_ALL_PRO = 0x101; // gather to all processors.

    /**
     * combine two different gather method: gather to root or gather to all processors.
     * @param ids global graph nodes ids will be saved in this array.
     * @param counts the nodes count of sub-graph on each processor.
     * @param root the rank id for root processor in ROOT_ONLY mode.
     * @param flag FLAG_ROOT_ONLY:gather to root or FLAG_ALL_PRO: gather to all processors.
     */
    void gatherAllNodesIds(_type_node_id *ids, _type_nodes_count *counts, const kiwi::RID root, const int flag);
};


#endif //PNOHS_GRAPH_H
