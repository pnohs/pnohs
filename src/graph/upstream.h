//
// Created by genshen on 2018-03-26.
//

#ifndef PNOHS_UPSTREAM_H
#define PNOHS_UPSTREAM_H


#include <vector>
#include "stream_meta.h"
#include "upstream_node.h"

class Upstream {
public:

    // node id of upstream nodes. Null or empty indicates that there is no upstream node.
    std::vector<UpstreamNode> nodes; // nodes meta information

    // count of upstream nodes of this node.
    inline unsigned long count() {
        return nodes.size(); // todo
    }

    // whether the upstream nodes of this node is ready to start a new time-step simulation.
    // That is the task queues of each upstream nodes are all not empty.
    bool isReady();

    // checkout whether there is a upstream node whose id is the given id,
    // if true, return pointer of th UpstreamNode, otherwise return null.
    UpstreamNode *findUpstreamNodeById(nodeid id);
};

#endif //PNOHS_UPSTREAM_H
