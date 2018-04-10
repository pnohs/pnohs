//
// Created by genshen on 2018-03-26.
//

#ifndef PNOHS_UPSTREAM_NODE_H
#define PNOHS_UPSTREAM_NODE_H


#include <deque>
#include <pthread.h>
//#include <concurrentqueue.hpp>
#include "stream_meta.h"
#include "../routing/type_routing.h"

class UpstreamNode : public StreamMeta {
public:

    /**
     * Initialize a UpstreamNode and whit its task queue.
     * And initialize pthread read-write lock here.
     */
    UpstreamNode();

    /**
     * check whether there is task in task queue.
     * @return
     */
    bool hasTask();

    /**
     * Get task count of this task queue.
     * It is just the queue size.
     * @return  count of tasks.
     */
    unsigned long taskCount();

    /**
     * Add a task to task queue.
     * This function is usually called when a stream routing from a node's upstream comes.
     * @param routing stream routing data.
     */
    void addTask(TypeRouting &routing);

private:
    // this is a shared variable, when it is modified by multiple thread, make sure to be thread-safe.
//    moodycamel::ConcurrentQueue<TypeRouting> task_queue;
    std::deque<TypeRouting> task_queue;
};

#endif //PNOHS_UPSTREAM_NODE_H
