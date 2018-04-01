//
// Created by genshen on 2018-03-26.
//

#ifndef PNOHS_STREAM_META_H
#define PNOHS_STREAM_META_H

#include <utils/data_def.h>
#include "../utils/typedef.h"

/**
 * meat data of upstream and downstream of node {@link node.h#node}.
 */
class StreamMeta {
public:
    // node id in graph.
    nodeid id;
    kiwi::RID location; // mpi int type.
    StreamMeta() = default;

    StreamMeta(nodeid id, kiwi::RID location);
};


#endif //PNOHS_STREAM_META_H
