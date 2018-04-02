//
// Created by genshen on 3/30/18.
//

#ifndef PNOHS_DISPATCH_TYPE_H
#define PNOHS_DISPATCH_TYPE_H

#include "../utils/typedef.h"

//Custom types used in reading subbasion info for improving maintainability
typedef unsigned long _type_dispatch_fileoffset;

typedef _type_graph_node_id _type_node_id; // node id type. // todo type redefine. _type_dispatch_node_id
typedef unsigned long _type_node_index; // node index type.
typedef kiwi::_type_io_offset _type_part_offset; // offset type. // todo combine with _type_dispatch_file_offset.
typedef _type_node_index _type_nodes_count; // node count type.

//typedef long _type_rank_id;   // use long here, while int is used in MPI.

#endif // PNOHS_DISPATCH_TYPE_H
