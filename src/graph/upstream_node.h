//
// Created by genshen on 2018-03-26.
//

#ifndef PNOHS_UPSTREAM_NODE_H
#define PNOHS_UPSTREAM_NODE_H


#include <deque>
#include "stream_meta.h"

class UpstreamNode : public StreamMeta {
public:
    // this is a shared variable, when it is modified by multiple thread, make sure to be thread-safe.
    std::deque<int> taskQueue; // todo thread safe.
    bool hasTask();
};

#endif //PNOHS_UPSTREAM_NODE_H
