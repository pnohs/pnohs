//
// Created by genshen on 3/30/18.
//

#ifndef PNOHS_PARTITION_TYPE_H
#define PNOHS_PARTITION_TYPE_H

//Custom types used in reading subbasion info for improving maintainability
typedef unsigned long _type_part_fileoffset;

typedef long _type_node_id; // node id type.
typedef unsigned long _type_node_index; // node index type.
typedef kiwi::_type_io_offset _type_part_offset; // offset type.
typedef _type_node_index _type_nodes_count; // node count type.

typedef long _type_rank_id;   // use long here, while int is used in MPI.

#endif //PNOHS_PARTITION_TYPE_H
