//
// Created by genshen on 8/16/18.
//

#include "graph_traversing.h"
#include "../utils/sim_domain.h"


Traversing::Traversing(Graph &sub_graph) : sub_graph(sub_graph), buffed_nodes_id() {}

void Traversing::resetTraversing() {
    traverse_list.clear();
//  todo  buffed_nodes_id clean
}

_type_node_id Traversing::nextNodeId() {
    _type_node_id next_id = NODE_ID_NULL;
    refresh_queue:
    if (!buffed_nodes_id.empty()) {
        // if buffer is not empty,
        // return the first node id from buffer queue (and remove this node id).
        next_id = buffed_nodes_id.front();
        buffed_nodes_id.pop();
        return next_id;
    } else {
        // todo move to a new function.
        _type_node_id local_id = getFreeLocalNode();
        // fetch nodes ids from all processors using mpi communication.
        _type_node_id *global_ids = new _type_node_id[domain::mpi_sim_process.all_ranks];
        MPI_Allgather(&local_id, sizeof(local_id), MPI_BYTE,
                      global_ids, sizeof(_type_node_id), MPI_BYTE,
                      domain::mpi_sim_process.comm);
        // filter null node id, then save left nodes id to queue.
        for (int i = 0; i < domain::mpi_sim_process.all_ranks; i++) {
            if (global_ids[i] != NODE_ID_NULL) {
                buffed_nodes_id.push(global_ids[i]);
                // once the node is accessed and added to buffer queue, this node will be tagged as visited.
                // tag upstream node or real node as visited.
                tagNodeTraversed(global_ids[i]);
            }
        }
        if (buffed_nodes_id.empty()) {
            // no more node id from global graph, traversing finish.
            return NODE_ID_NULL;
        }
        goto refresh_queue; // access node id from buffer again.
    }
}

const _type_node_id Traversing::getFreeLocalNode() {
    for (Node &node:sub_graph.nodes) {
        // we need check whether this node have been added to @var traversed_list (tagged as traversed).
        if (hasTraversed(node.id)) {
            continue;
        }
        // just check if all upstream nodes of some node has been added to @var traversed_list.
        // For nodes whose indegree is zero (have no upstream nodes),
        // upstream nodes in @var traversed_list checking will pass naturally.
        for (UpstreamNode up_node: node.upstream.nodes) {
            if (!hasTraversed(up_node.id)) { // this upstream node has not been traversed.
                goto next_node;
            }
        }
        // all completed.
        return node.id;
        next_node: ;
    }
    return NODE_ID_NULL;
}

void Traversing::tagNodeTraversed(const _type_node_id id) {
    if (id == NODE_ID_NULL) {
        return;
    }
    for (Node &node:sub_graph.nodes) {
        if (node.id == id) { // real node
            traverse_list.insert(id);
            break;
        } else if (node.upstream.findUpstreamNodeById(id) != nullptr) { // upstream node
            traverse_list.insert(id);
            break;
        }
    }
}
