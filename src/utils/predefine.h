//
// Created by genshen on 3/26/18.
//

#ifndef PNOHS_TYPEDEF_H
#define PNOHS_TYPEDEF_H

#include <cstddef>
#include <string>
#include <mpi.h>

// graph
typedef unsigned long _type_node_id;
typedef unsigned long _type_node_index; // node index type.
typedef size_t _type_nodes_count; // node count type.

const _type_node_id NODE_ID_NULL = 0;

// params
typedef size_t _type_params_count;

const MPI_Datatype _type_param_mpi = MPI_DOUBLE;

// mpi message
const int TagStreamRoutingMessage = 0x101;

// type define of model id and model key.
typedef unsigned long _type_model_id;
typedef std::string _type_model_key;

#endif //PNOHS_TYPEDEF_H
