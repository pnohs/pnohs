//
// Created by genshen on 2018-03-26.
//

#include "upstream.h"

Upstream::Upstream() {
    pthread_rwlock_init(&_task_queue_rwlock, nullptr);
}

bool Upstream::isReady() {
    // if the node has no upstreams (nodes.empty is true), then this simulation node can be returned directly.
    pthread_rwlock_rdlock(&_task_queue_rwlock);
    for (UpstreamNode &node:nodes) {
        if (!node.hasTask()) {
            pthread_rwlock_unlock(&_task_queue_rwlock);
            return false;
        }
    }
    pthread_rwlock_unlock(&_task_queue_rwlock);
    return true;
}

unsigned long Upstream::minQueSize() {
    return 0; // todo
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

bool Upstream::appendUpstreamRouting(_type_node_id upstream_node_id, TypeRouting &task) {
    UpstreamNode *up_node = findUpstreamNodeById(upstream_node_id);
    if (up_node == nullptr) {
        return false; // normally, this branch should not be reached.
    }

    // write task to task queue.
    pthread_rwlock_wrlock(&_task_queue_rwlock);
    up_node->addTask(task);
    pthread_rwlock_unlock(&_task_queue_rwlock);
    return true;
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
