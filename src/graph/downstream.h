//
// Created by genshen on 2018-03-26.
//

#ifndef PNOHS_DOWNSTREAM_H
#define PNOHS_DOWNSTREAM_H

#include <vector>
#include "stream_meta.h"
#include "downstream_node.h"

/**
 * Usually, there is only one downstream node.
 * not just like upstream (a node may have multiple upstream nodes).
 */

class Downstream {
public:

    /**
     * Downstream nodes.
     * Empty indicates that there is no downstream node, that is the node this the river outlet..
     * For a given node, it usually has only one downstream node. (That is the length of is usually 1 or 0).
     */
    std::vector<DownstreamNode> nodes;

    /**
     * Check whether this node is the river outlet.
     * @return
     */
    inline bool isOutlet() {
        return nodes.empty();
    }

    /**
     * add a node with meta data to downstream nodes vector @var downstreamNodes.
     * @param meta
     */
    void putDownMetaStream(const StreamMeta &meta);
};

#endif //PNOHS_DOWNSTREAM_H
