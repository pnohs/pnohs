//
// Created by genshen on 2018-03-26.
//

#ifndef PNOHS_NODE_H
#define PNOHS_NODE_H

#include <vector>
#include "stream_meta.h"
#include "upstream.h"
#include "downstream.h"
#include "../utils/typedef.h"

/**
 * Node in river-routing relationship graph.
 * Node is a simulation unit (e.g. sub-basin, hydrological response unit(HRU)) in geography.
 * In our graph, node refers to simulation unit, vertex refers to river-routing relationship from upstream to downstream.
 */

class Node {
public:
    nodeid id; // node id.

    double area;  // todo example property of this node.

    // upstream of this node.
    Upstream upstream;

    // downstream of this node (usually,it has only one downstream node).
    Downstream downstream;

};

#endif //PNOHS_NODE_H
