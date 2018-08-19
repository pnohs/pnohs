//
// Created by genshen on 8/16/18.
//

#ifndef PNOHS_GRAPH_TRAVERSING_H
#define PNOHS_GRAPH_TRAVERSING_H

#include <set>
#include "graph.h"
#include "../utils/predefine.h"


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


private:
    /**
     * reference to a sub graph, traversing will start from those {@var sub_graph} on all processor.
     */
    Graph &sub_graph;

    /**
     * {@var traversing} recording the nodes has been traveled.
     * If some node has been traveled, the id of this node will be added to this set.
     */
    std::set<_type_node_id> traversing;
};


#endif //PNOHS_GRAPH_TRAVERSING_H
