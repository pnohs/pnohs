//
// Created by genshen on 2018-03-26.
//

#include "upstream_node.h"

UpstreamNode::UpstreamNode() : StreamMeta(), taskQueue() {
}

bool UpstreamNode::hasTask() { // todo
    return !taskQueue.empty();
}
