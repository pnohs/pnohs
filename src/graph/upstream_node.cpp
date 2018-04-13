//
// Created by genshen on 2018-03-26.
//

#include "upstream_node.h"

UpstreamNode::UpstreamNode() : StreamMeta(), task_queue() {
}

bool UpstreamNode::hasTask() {
    return !task_queue.empty();
}

unsigned long UpstreamNode::taskCount() {
    return task_queue.size();
}

void UpstreamNode::addTask(TypeRouting &routing_task) {
    task_queue.push_back(routing_task);
}

TypeRouting UpstreamNode::popTaskNoEmpty() {
    TypeRouting frontest = task_queue.front();
    task_queue.pop_front();
    return frontest;
}
