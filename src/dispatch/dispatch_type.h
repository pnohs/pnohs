//
// Created by genshen on 3/30/18.
//

#ifndef PNOHS_DISPATCH_TYPE_H
#define PNOHS_DISPATCH_TYPE_H

#include "../utils/predefine.h"

//Custom types used in reading subbasion info for improving maintainability

typedef _type_node_id _type_dispatch_node_id; // node id type.
typedef kiwi::_type_io_offset _type_dispatch_file_offset; // offset type.

typedef _type_node_index _type_dispatch_node_index; // node index type.
typedef _type_nodes_count _type_dispatch_nodes_count; // node count type.

typedef kiwi::RID _type_dispatch_rank_id;   // use long here, while int is used in MPI.

#endif // PNOHS_DISPATCH_TYPE_H
