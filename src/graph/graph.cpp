//
// Created by genshen on 8/16/18.
//

#include <iterator>
#include <mpi.h>
#include "graph.h"
#include "../utils/sim_domain.h"

void Graph::addNode(Node &node) {
    for (Node &_node:nodes) {
        if (_node.id == node.id) {
            return; // if this node exists.
        }
    }
    nodes.push_back(node);
}

void Graph::globalNodesCount(_type_nodes_count *counts) {
//#if __cplusplus >= 201103L
//    auto array_length = std::end(counts) - std::begin(counts)
//#endif
    _type_nodes_count my_node_count = nodes.size();
    MPI_Allgather(&my_node_count, sizeof(_type_nodes_count), MPI_BYTE,
                  counts, sizeof(_type_nodes_count), MPI_BYTE,
                  domain::mpi_sim_process.comm);
}

void Graph::getGraphNodesIds(_type_node_id *ids) {
    int i = 0;
    for (Node &node: nodes) {
        ids[i++] = node.id;
    }
}

std::vector<_type_node_id> Graph::getGraphNodesIds() {
    std::vector<_type_node_id> ids(nodesCount());
    int i = 0;
    for (Node &node: nodes) {
        ids[i++] = node.id;
    }
    return ids;
}
