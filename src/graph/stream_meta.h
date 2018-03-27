//
// Created by genshen on 2018-03-26.
//

#ifndef PNOHS_STREAM_META_H
#define PNOHS_STREAM_META_H

#include "../utils/typedef.h"

/**
 * meat data of upstream and downstream of node {@link node.h#node}.
 */
class StreamMeta {
public:
    // node id in graph.
    nodeid id;
    int location; // mpi int type.
};


#endif //PNOHS_STREAM_META_H
