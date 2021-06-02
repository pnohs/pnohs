//
// Created by genshen on 9/12/18.
//

#include "api_graph_meta.h"

kiwi::RID ApiGraphMeta::locateRank(const _type_node_id id) {
    if (g_nodes_counts == nullptr || g_nodes_id_lists == nullptr) {
        return RANK_NOT_FOUND;
    }
    _type_nodes_count index = 0;
    for (int pid = 0; pid < d.all_ranks; pid++) {
        for (int j = 0; j < g_nodes_counts[pid]; j++) {
            if (g_nodes_id_lists[index] == id) {
                return pid;
            }
            index++;
        }
    }
    return RANK_NOT_FOUND;
}

ApiGraphMeta GraphMetaBuilder::build() {
    ApiGraphMeta graph_meta;
    // assigned
    graph_meta.graph = this->graph;
    graph_meta.d = this->d;
    // initialize graph.
    this->graph_builder(graph_meta.graph);

    // get nodes count of all processors in simulation domain.
    graph_meta.g_nodes_counts = new _type_nodes_count[d.all_ranks];
    graph_meta.graph->globalNodesCount(graph_meta.g_nodes_counts);

    // local nodes count
    graph_meta.local_nodes_count = graph_meta.graph->nodesCount();
    // set total nodes count.
    _type_nodes_count sum = 0; // compute all nodes count.
    for (int i = 0; i < d.all_ranks; i++) {
        sum += graph_meta.g_nodes_counts[i];
    };
    graph_meta.g_total_nodes_count = sum;

    // get global nodes id list.
    if (d.own_rank == root) {
        graph_meta.g_nodes_id_lists = new _type_node_id[sum];
    }
    graph_meta.graph->gatherNodesIds(graph_meta.g_nodes_id_lists, graph_meta.g_nodes_counts,
                                     root); // global only on root.
    // set local nodes.The global ids is just a join of local nodes id from all processor.
    graph_meta.local_nodes_id_lists = new std::vector<_type_node_id>();
    *(graph_meta.local_nodes_id_lists) = graph_meta.graph->getLocalGraphNodesIds(); // todo better code, // todo data copy.
    return graph_meta;
}

void GraphMetaBuilder::destroyMetaEntity(ApiGraphMeta meta) {
    delete[]meta.g_nodes_counts;
    delete[]meta.g_nodes_id_lists;
    delete meta.local_nodes_id_lists;
    delete meta.graph;
    meta.g_nodes_counts = nullptr;
    meta.g_nodes_id_lists = nullptr;
    meta.local_nodes_id_lists = nullptr;
    meta.graph = nullptr;
}
