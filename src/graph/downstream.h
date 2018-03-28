//
// Created by genshen on 2018-03-26.
//

#ifndef PNOHS_DOWNSTREAM_H
#define PNOHS_DOWNSTREAM_H

#include "stream_meta.h"
#include "downstream_node.h"

// usually, there is only one downstream node.
// not just like upstream (a node may have multiple upstream nodes).

class Downstream {
public:
    // node id of downstream node. Null or empty indicates that there is no downstream node.
    // but usually, for a given node, it is has only one downstream node. (That is the length of is usually 1 or 0).
    DownstreamNode downstreamNode;
};

#endif //PNOHS_DOWNSTREAM_H
