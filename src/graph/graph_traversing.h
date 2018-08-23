//
// Created by genshen on 8/16/18.
//

#ifndef PNOHS_GRAPH_TRAVERSING_H
#define PNOHS_GRAPH_TRAVERSING_H

#include <set>
#include <queue>
#include "graph.h"
#include "../utils/predefine.h"

/**
 * the algorithm of traversing graph:
 * 0. Initialize a empty nodes buffer.
 * 1. check buffer, if buffer is empty, continue. Else, go to step 4.
 * 2. Each processor contribute a node whose upstream is empty or all its upstreams are tagged as traversed.
 *    if the satisfied node does exits, an null node will be contributed.
 * 3. Save all the nodes (exclude null node) from each processor to a buffer.
 * 4. If buffer is empty, return an null node (traversing finished, exist.);
 *    Else select a node from buffer, and return it (goto step 1).
 */
class Traversing {
public:
    /**
     * initialize traversing with a given sub-graph.
     * all sub-graphs in all processor in simulation domain consists a complete graph.
     * @param sub_graph a sub graph @see {@link graph.h}
     */
    explicit Traversing(Graph &sub_graph);

    /**
     * reset set {@var traversing}.
     * after resetting, we can restart a new graph traversing.
     */
    void resetTraversing();

    /**
     * It returns a node id from global graph.
     * After the node is returned, the node will be tagged as traversed in @var traversed.
     * If there is no more untagged node in global graph, an null node will be returned.
     *
     * After calling this function, all processors in simulation domain will get a node id(or null node id).
     * And they are all the same.
     *
     * @note this function should all processors in simulation domain
     * (because MPI_AllGather is involved, besides buffed data in all processors should be the same).
     *
     * @return node id for next ndode
     */
    _type_node_id nextNodeId();

    /**
     * It returns a node form local sub-graph.
     * The node must satisfy following rules:
     * 0. This node are not tagged as traversed.
     * 1. The indegree of the node equals to 0 (without upstreams).
     * 2. if there is no node satisfy rule 1,
     *    a node will be ok if all its direct indegree nodes(nodes contribute indegree
     *    to this node directly, or saying all its direct upstream nodes) are tagged as traversed.
     * 3. if there is no node satisfy rule 1 and rule 2, the node can be an null node.
     * @return id of a node satisfying above rules, or an null node id.
     */
    const _type_node_id getFreeLocalNode();

private:
    /**
     * reference to a sub graph, traversing will start from those {@var sub_graph} on all processor.
     */
    Graph &sub_graph;

    std::queue<_type_node_id> buffed_nodes_id;

    /**
     * {@var traversing} recording the nodes has been traveled.
     * If some node has been traveled, the id of this node will be added to this set.
     */
    std::set<_type_node_id> traverse_list;

    /**
     * check whether a node have been traversed,
     * Just checking whether this node is in @var traverse_list.
     * @param id node id
     * @return true for has been traversed, false for has not been traversed.
     */
    inline bool hasTraversed(const _type_node_id id) {
        return traverse_list.find(id) != traverse_list.end();
    }

    /**
     * tag a node as traversed.
     * The node id will be verified first to make sure
     * and this node is a node on this processor or it is a upstream node of a node on this processor.
     * Besides, this node would not be an null node.
     * Only the verification passed, can the node be added to traversed list.
     * @param id node id
     */
    void tagNodeTraversed(const _type_node_id id);
};


#endif //PNOHS_GRAPH_TRAVERSING_H
