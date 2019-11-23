//
// Created by genshen on 4/9/18.
//

#ifndef PNOHS_TYPE_ROUTING_H
#define PNOHS_TYPE_ROUTING_H

#include "../utils/predefine.h"

/**
 * basic data type for river/stream routing communication among processors.
 */
struct TypeRouting {
    // todo: use vector pointer to reduce data copy
    typedef double tp_routing_data;

    /**
     * Considering deliver routing results to its downstream node, denoted as D,
     * the source_id is the id of the upstream node of D.
     */
    _type_node_id source_id;

    /**
     * destination_id is the id of downstream node D.
     */
    _type_node_id destination_id;

    /**
     * stream routing data.
     */
    tp_routing_data routing_data;

    TypeRouting() = default;

    TypeRouting(_type_node_id source, _type_node_id des);


};

#endif //PNOHS_TYPE_ROUTING_H
