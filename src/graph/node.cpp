//
// Created by genshen on 2018-03-26.
//

#include "node.h"

//
//void Node::select() {
//
//}
Node::Node(const _type_node_id id) : id(id) {}

void Node::notifyDataSetChanged() {
    _is_river_outlet = downstream.nodes.empty();
    _is_river_origin = (upstream.count() == 0);
}
