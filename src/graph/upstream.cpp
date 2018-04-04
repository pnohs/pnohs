//
// Created by genshen on 2018-03-26.
//

#include "upstream.h"

bool Upstream::isReady() {
    // if the node has no upstreams (nodes.empty is true), then this simulation node can be returned directly.
    for (UpstreamNode &node:nodes) {
        if (!node.hasTask()) {
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
