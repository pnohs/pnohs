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

void Graph::globalNodesCount(_type_nodes_count *counts, kiwi::RID root) {
    _type_nodes_count my_node_count = nodes.size();
    MPI_Gather(&my_node_count, sizeof(_type_nodes_count), MPI_BYTE,
               counts, sizeof(_type_nodes_count), MPI_BYTE,
               root, domain::mpi_sim_process.comm);
}

void Graph::getLocalGraphNodesIds(_type_node_id *ids) {
    int i = 0;
    for (Node &node: nodes) {
        ids[i++] = node.id;
    }
}

std::vector<_type_node_id> Graph::getLocalGraphNodesIds() {
    std::vector<_type_node_id> ids(nodesCount());
    int i = 0;
    for (Node &node: nodes) {
        ids[i++] = node.id;
    }
    return ids;
}


/**
 * the array ids for all ranks will be the same: 9,2,3,10,4,7,8,5,6,3
 * ALL_GLOBAL mode
       local nodes ids | counts [in] |  ids [out]
rank 0: 9, 2, 3, 10    |  4,3,3,3   | 9,2,3,10,4,7,8,5,6,3
rank 1: 4, 7, 8        |  4,3,3,3   | 9,2,3,10,4,7,8,5,6,3
rank 2: 5, 6, 3        |  4,3,3,3   | 9,2,3,10,4,7,8,5,6,3
*/
void Graph::gatherNodesIds(_type_node_id *ids, _type_nodes_count *counts) {
    if (counts[domain::mpi_sim_process.own_rank] != nodesCount()) {
        throw std::invalid_argument("invalid nodes count in counts array");
    }

    // set displace and receive count.
    int *displace = new int[domain::mpi_sim_process.all_ranks];
    int *rev_count = new int[domain::mpi_sim_process.all_ranks];
    int offset = 0;
    for (int i = 0; i < domain::mpi_sim_process.all_ranks; i++) {
        // receive count must be int array; and data type is _type_node_id.
        rev_count[i] = static_cast<int>(counts[i]) * sizeof(_type_node_id);
        displace[i] = offset * sizeof(_type_node_id);
        offset += counts[i]; // set next offset.
    }

    // load local nodes ids.
    _type_nodes_count local_nodes_count = nodesCount();
    _type_node_id *local_ids = new _type_node_id[local_nodes_count];
    getLocalGraphNodesIds(local_ids);

    // after sending, the array ids on each processor will have the same data (global nodes ids).
    MPI_Allgatherv(local_ids, static_cast<int>(local_nodes_count * sizeof(_type_node_id)), MPI_BYTE,
                   ids, rev_count, displace, MPI_BYTE, domain::mpi_sim_process.comm);

    delete[]local_ids;
    delete[]rev_count;
    delete[]displace;
}

/*
 * ROOT_ONLY mode
       local nodes ids | counts [in] |  ids [out]
rank 0: 9, 2, 3, 10    |  4,3,3,3   | 9,2,3,10,4,7,8,5,6,3
rank 1: 4, 7, 8        |  4,3,3,3   | _ _ _
rank 2: 5, 6, 3        |  4,3,3,3   | _ _ _
*/
void Graph::gatherNodesIds(_type_node_id *ids, _type_nodes_count *counts, kiwi::RID root) {
    int *displace = nullptr, *rev_count = nullptr;
    // set displace and rec_count for root processor, the other processors keep empty.
    if (domain::mpi_sim_process.own_rank == root) {
        displace = new int[domain::mpi_sim_process.all_ranks];
        rev_count = new int[domain::mpi_sim_process.all_ranks];
        int offset = 0;
        for (int i = 0; i < domain::mpi_sim_process.all_ranks; i++) {
            // receive count must be int array; and data type is _type_node_id.
            rev_count[i] = static_cast<int>(counts[i]) * sizeof(_type_node_id);
            displace[i] = offset * sizeof(_type_node_id);
            offset += counts[i]; // set next offset.
        }
    }

    // load local nodes ids.
    _type_nodes_count local_nodes_count = nodesCount();
    _type_node_id *local_ids = new _type_node_id[local_nodes_count];
    getLocalGraphNodesIds(local_ids);

    // after syncing nodes ids to root processors,
    // the array ids on each processor will have the same data (global nodes ids).
    MPI_Gatherv(local_ids, static_cast<int>(local_nodes_count * sizeof(_type_node_id)), MPI_BYTE,
                ids, rev_count, displace, MPI_BYTE,
                root, domain::mpi_sim_process.comm);

    delete[]local_ids;
    delete[]rev_count;
    delete[]displace;

//    // set offset position.
//    int offset = 0;
//    for (int i = 0; i < domain::mpi_sim_process.own_rank; i++) {
//        offset += counts[i];
//    }
//    // fill array ids with local nodes ids.
//    // (fill array with ids of sub-graph nodes on this processor).
//    getLocalGraphNodesIds(ids + offset);
//
//    // sync nodes ids to other processors(master or all other processors).
//    _type_nodes_count total_nodes = 0;
//    for (int i = 0; i < domain::mpi_sim_process.all_ranks; i++) {
//        total_nodes += counts[i];
//    }
}