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
    std::vector<UpstreamNode> nodes; // nodes meta information // todo make private.

    // count of upstream nodes of this node.
    inline const unsigned long count() {
        return nodes.size(); // todo
    }

    // whether the upstream nodes of this node is ready to start a new time-step simulation.
    // That is the task queues of each upstream nodes are all not empty.
    bool isReady();

    /**
     * checkout whether there is a upstream node whose id is the given id,
     * returns pointer of UpstreamNode if found.
     * @param id node id
     * @return if true, return pointer of this UpstreamNode, otherwise return null.
     */
    UpstreamNode *findUpstreamNodeById(_type_node_id id);

    /**
     * add a upstream node to vector @var nodes and create a queue for this node
     * It is used when doing stream parsing.
     */
    void putUpMetaStream(const StreamMeta &meta);
};

#endif //PNOHS_UPSTREAM_H
