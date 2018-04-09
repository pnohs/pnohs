//
// Created by genshen on 4/9/18.
//

#ifndef PNOHS_TYPE_ROUTING_H
#define PNOHS_TYPE_ROUTING_H

#include "../utils/typedef.h"

/**
 * basic data type for river/stream routing communication among processors.
 */
struct TypeRouting {
//    kiwi::RID ird;
    _type_node_id nodeid;
    _type_node_id downstream_nodeid;
    double routing_data; // just an example of stream routing data.

};

#endif //PNOHS_TYPE_ROUTING_H
