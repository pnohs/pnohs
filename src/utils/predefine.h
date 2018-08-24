//
// Created by genshen on 3/26/18.
//

#ifndef PNOHS_TYPEDEF_H
#define PNOHS_TYPEDEF_H

#include <cstddef>

// graph
typedef unsigned long _type_node_id;
typedef unsigned long _type_node_index; // node index type.
typedef size_t _type_nodes_count; // node count type.

static const _type_node_id NODE_ID_NULL = 0;

// params
typedef size_t _type_params_count;

// mpi message
static const int TagStreamRoutingMessage = 0x101;

#endif //PNOHS_TYPEDEF_H
