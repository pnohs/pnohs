//
// Created by genshen on 8/23/18.
//

#include <gtest/gtest.h>
#include <graph/graph_traversing.h>
#include "generate_graph.hpp"

TEST(traversing_test_nextnode_all_ids, traversing_test) {
    domain::mpi_sim_process = kiwi::mpiUtils::global_process;

    Graph graph = genSubGraphForTest();
    Traversing travers(graph);

    _type_node_id id;
    std::list<_type_node_id> ids;
    while ((id = travers.nextNodeId()) != NODE_ID_NULL) {
        ids.push_back(id); // save all id
    }
    ids.sort();

    // testing all nodes have got.
    int i = 0;
    for (_type_node_id _id:ids) {
        i++;
        EXPECT_EQ(_id, i);
    }
}
