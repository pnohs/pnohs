//
// Created by genshen on 8/23/18.
//

#ifndef PNOHS_GEN_GRAPH_H
#define PNOHS_GEN_GRAPH_H

#include <utils/predefine.h>
#include <graph/graph.h>
#include <utils/sim_domain.h>

/**
 * graph dispatch in this test, we use binary code tree encoding.
rank 2: O(2,0) O(2,1) O(2,2) O(2,3)
            \   /       \   /
rank 1:    O(1,0)      O(1,1)
              \       /
rank 0:        O(0,0)

---------------------
 for node O(L,V), the node id = 2^(rank) + V.
 nodes ids: 1 <- 2( <- 4,5), 3( <- 6,7).
 */
inline _type_node_id NODE_ID(int L, int V) { return static_cast<_type_node_id>((1 << L) + V); }

inline Graph genSubGraphForTest() {
    Graph graph;
    const int L = domain::mpi_sim_process.own_rank;
    // in this test, rank i will have i+1 node(s). e.g. rank 0 have 1 node; rank 4 have 5 nodes.
    for (int V = 0; V < (1 << L); V++) { // V_max = 2^L -1
        Node node(NODE_ID(L, V));

        // the nodes on the last rank have no upstream
        if (L + 1 != domain::mpi_sim_process.all_ranks) {
            // add upstream nodes.
            // assume this node is (L,V), then the downstream node will be (L+1, V*2) and (L+1, V*2+1).
            node.upstream.putUpMetaStream(StreamMeta(NODE_ID(L + 1, V * 2), L + 1));
            node.upstream.putUpMetaStream(StreamMeta(NODE_ID(L + 1, V * 2 + 1), L + 1));
        }
        // the nodes on the first rank have no downstream.
        if (L != 0) {
            // assume this node is (L,V), then the downstream node will be (L-1, V/2).
            node.downstream.putDownMetaStream(StreamMeta(NODE_ID(L - 1, V / 2), L - 1));
        }
        node.notifyDataSetChanged();
        graph.addNode(node);
    }
    return graph;
}

#endif //PNOHS_GEN_GRAPH_H
