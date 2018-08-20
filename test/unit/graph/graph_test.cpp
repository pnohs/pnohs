//
// Created by genshen on 8/19/18.
//

#include <gtest/gtest.h>
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

Graph genSubGraphForTest() {
    Graph graph;
    const int L = domain::mpi_sim_process.own_rank;
    // in this test, rank i will have i+1 node(s). e.g. rank 0 have 1 node; rank 4 have 5 nodes.
    for (int V = 0; V < (1 << L); V++) { // V_max = 2^L -1
        Node node;
        node.id = NODE_ID(L, V);

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

TEST(graph_node_count, graph_test) {
    domain::mpi_sim_process = kiwi::mpiUtils::global_process;

    Graph graph = genSubGraphForTest();
    // test node count for sub-graph.
    EXPECT_EQ(graph.nodesCount(), 1 << domain::mpi_sim_process.own_rank);
}

TEST(graph_get_node_ids, graph_test) {
    domain::mpi_sim_process = kiwi::mpiUtils::global_process;

    Graph graph = genSubGraphForTest();
    const _type_nodes_count ids_length = graph.nodesCount();
    auto *ids = new _type_node_id[ids_length];
    graph.getLocalGraphNodesIds(ids); // test this function.

    // sort ids
    std::vector<int> ids_vector(ids, ids + ids_length);
    std::sort(ids_vector.begin(), ids_vector.end());

    for (int i = 0; i < ids_length; i++) {
        EXPECT_EQ(ids_vector[i], NODE_ID(domain::mpi_sim_process.own_rank, i));
    }
    delete[]ids;
}

TEST(graph_get_node_ids_2_vector, graph_test) {
    domain::mpi_sim_process = kiwi::mpiUtils::global_process;

    Graph graph = genSubGraphForTest();
    const _type_nodes_count ids_length = graph.nodesCount();

    std::vector<_type_node_id> ids_vector = graph.getLocalGraphNodesIds(); // test this function.

    // sort ids
    std::sort(ids_vector.begin(), ids_vector.end());

    for (int i = 0; i < ids_length; i++) {
        EXPECT_EQ(ids_vector[i], NODE_ID(domain::mpi_sim_process.own_rank, i));
    }
}

// test Graph::globalNodesCount
TEST(graph_global_nodes_count, graph_test) {
    domain::mpi_sim_process = kiwi::mpiUtils::global_process;
    Graph graph = genSubGraphForTest();

    _type_nodes_count *all_count = new _type_nodes_count[domain::mpi_sim_process.all_ranks];
    graph.globalNodesCount(all_count);
    for (int i = 0; i < domain::mpi_sim_process.all_ranks; ++i) {
        EXPECT_EQ(all_count[i], 1 << i);
    }
    delete[]all_count;
}

TEST(graph_global_nodes_count_2_root, graph_test) {
    domain::mpi_sim_process = kiwi::mpiUtils::global_process;
    Graph graph = genSubGraphForTest();

    _type_nodes_count *all_count = new _type_nodes_count[domain::mpi_sim_process.all_ranks];
    const int unchanged = 0x1234;
    for (int i = 0; i < domain::mpi_sim_process.all_ranks; i++) {
        all_count[i] = unchanged;
    }

    graph.globalNodesCount(all_count, MASTER_PROCESSOR);
    for (int i = 0; i < domain::mpi_sim_process.all_ranks; ++i) {
        if (domain::mpi_sim_process.own_rank == MASTER_PROCESSOR) {
            EXPECT_EQ(all_count[i], 1 << i);
        } else {
            EXPECT_EQ(all_count[i], unchanged);
        }
    }
    delete[]all_count;
}

TEST(graph_global_nodes_count_2_root_null, graph_test) {
    domain::mpi_sim_process = kiwi::mpiUtils::global_process;
    Graph graph = genSubGraphForTest();

    _type_nodes_count *all_count = nullptr;
    // one allocate memory for master, the other processor will keep null.
    if (domain::mpi_sim_process.own_rank == MASTER_PROCESSOR) {
        all_count = new _type_nodes_count[domain::mpi_sim_process.all_ranks];
    }

    graph.globalNodesCount(all_count, MASTER_PROCESSOR);

    if (domain::mpi_sim_process.own_rank == MASTER_PROCESSOR) {
        for (int i = 0; i < domain::mpi_sim_process.all_ranks; ++i) {
            EXPECT_EQ(all_count[i], 1 << i);
        }
    }
    delete[]all_count;
}

// Graph::gatherNodesIds
TEST(graph_gather_nodes_ids, graph_test) {
    domain::mpi_sim_process = kiwi::mpiUtils::global_process;
    Graph graph = genSubGraphForTest();

    // set global nodes count
    _type_nodes_count *all_count = new _type_nodes_count[domain::mpi_sim_process.all_ranks];
    _type_nodes_count nodes_count_sum = 0;
    for (int i = 0; i < domain::mpi_sim_process.all_ranks; ++i) {
        all_count[i] = static_cast<_type_nodes_count>(1 << i);
        nodes_count_sum += all_count[i];
    }
    // the nodes count in global graph will be: 2^(all_ranks) -1
    EXPECT_EQ(nodes_count_sum, (1 << domain::mpi_sim_process.all_ranks) - 1);

    // allocate mem for ids, and run getting global nodes ids.
    _type_node_id *ids = new _type_node_id[nodes_count_sum];
    graph.gatherNodesIds(ids, all_count);

    for (int i = 0; i < nodes_count_sum; ++i) {
        EXPECT_EQ(ids[i], i + 1); // in this case, ids will be sort for litter to big, starting from 1.
    }

    delete[]all_count;
    delete[]ids;
}

TEST(graph_gather_nodes_ids_2_root, graph_test) {
    domain::mpi_sim_process = kiwi::mpiUtils::global_process;
    Graph graph = genSubGraphForTest();

    // set global nodes count on each processor.
    _type_nodes_count *all_count = new _type_nodes_count[domain::mpi_sim_process.all_ranks];
    _type_nodes_count nodes_count_sum = 0;
    for (int i = 0; i < domain::mpi_sim_process.all_ranks; ++i) {
        all_count[i] = static_cast<_type_nodes_count>(1 << i);
        nodes_count_sum += all_count[i];
    }
    // the nodes count in global graph will be: 2^(all_ranks) -1
    EXPECT_EQ(nodes_count_sum, (1 << domain::mpi_sim_process.all_ranks) - 1);

    // allocate mem for ids, and run getting global nodes ids.
    _type_node_id *ids = new _type_node_id[nodes_count_sum];
    const int unchanged = 0x89DF;
    for (int i = 0; i < nodes_count_sum; i++) {
        ids[i] = unchanged;
    }
    graph.gatherNodesIds(ids, all_count, MASTER_PROCESSOR);

    for (int i = 0; i < nodes_count_sum; ++i) {
        if (domain::mpi_sim_process.own_rank == MASTER_PROCESSOR) {
            EXPECT_EQ(ids[i], i + 1); // in this case, ids will be sort for litter to big, starting from 1.
        } else {
            EXPECT_EQ(ids[i], unchanged);
        }
    }

    delete[]all_count;
    delete[]ids;
}
