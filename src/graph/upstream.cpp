//
// Created by genshen on 2018-03-26.
//

#include "upstream.h"

bool Upstream::isReady() {
    for (UpstreamNode &node:nodes) { // todo: refer to the node, not copy.
        if (node.hasTask()) {
            return false;
        }
    }
    return true;
}

UpstreamNode *Upstream::findUpstreamNodeById(nodeid id) {
    for (UpstreamNode &node:nodes) {
        if (node.id == id) {
            return &node;
        }
    }
    return nullptr;
}
