//
// Created by genshen on 2018-03-26.
//

#include "upstream.h"

bool Upstream::isReady() {
    // if the node has no upstreams (nodes.empty is true), then this simulation node can be returned directly.
    for (UpstreamNode &node:nodes) {
        if (!node.hasTask()) { // todo lock
            return false;
        }
    }
    return true;
}

UpstreamNode *Upstream::findUpstreamNodeById(_type_node_id id) {
    for (UpstreamNode &node:nodes) {
        if (node.id == id) {
            return &node;
        }
    }
    return nullptr;
}

void Upstream::putUpMetaStream(const StreamMeta &meta) {
    UpstreamNode up_node = UpstreamNode(); //an empty task queue is initialed here.

    up_node.id = meta.id;
    up_node.location = meta.location;
    // todo set value in vector.
    nodes.push_back(up_node);
}

void Upstream::appendUpstreamRouting(_type_node_id upstream_node_id, TypeRouting &data) {
// todo enqueue using std::mutex or pthread mutex.
    // find upstream,
    // mutex.lock();
    //   append to task queue.
    // mutex.unlock();
}

std::list<TypeRouting> Upstream::deQueue() {
    // todo using std::mutex or pthread mutex.
    /**
     * var list = std::list();
     * mutex.lock();
     * for var node : nodes{
     *   var routing = node.taskqueue.dequeue();
     *   list.push_back(routing);
     * }
     * mutex.unlock();
     */
    return std::list<TypeRouting>();
}
