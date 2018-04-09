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
    /**
     * Considering deliver routing results to its downstream node, denoted as D,
     * the source_id is the id of the upstream node of D.
     */
    _type_node_id source_id;

    /**
     * destination_id is the id of downstream node D.
     */
    _type_node_id destination_id;
    double routing_data; // just an example of stream routing data.

};

#endif //PNOHS_TYPE_ROUTING_H
