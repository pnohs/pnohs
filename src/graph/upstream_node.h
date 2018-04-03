//
// Created by genshen on 2018-03-26.
//

#ifndef PNOHS_UPSTREAM_NODE_H
#define PNOHS_UPSTREAM_NODE_H


#include <deque>
#include "stream_meta.h"

class UpstreamNode : public StreamMeta {
public:
    /**
     * initial a UpstreamNode and whit its task queue.
     */
    UpstreamNode();

    /**
     * check whether there is task in task queue.
     * @return
     */
    bool hasTask();

private:
    // this is a shared variable, when it is modified by multiple thread, make sure to be thread-safe.
    // todo thread safe, lock.
    std::deque<double> taskQueue;
};

#endif //PNOHS_UPSTREAM_NODE_H
