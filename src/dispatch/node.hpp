//
// Created by genshen on 4/1/18.
//

#ifndef PNOHS_D_NODE_H
#define PNOHS_D_NODE_H

#include <vector>
#include "../graph/stream_meta.h"
#include "dispatch_type.h"

// node information, including upstream and downstream nodes metadata.
class DNode {
public:
    _type_node_id node_id; // todo make it read only.

    DNode() : node_id(0), upstreamNodesMeta(), downstreamNodesMeta(),
              upstream_nodes_count(0), downstream_nodes_count(0) {}

    const std::vector<StreamMeta> &getUpstreamNodes() const {
        return upstreamNodesMeta;
    }

    const std::vector<StreamMeta> &getDownstreamNodes() const {
        return downstreamNodesMeta;
    }

    const _type_nodes_count getUpstreamNodesCount() const {
        return upstream_nodes_count;
    }

    const _type_nodes_count getDownstreamNodesCount() const {
        return downstream_nodes_count;
    }

    void addUpstreamNode(const StreamMeta &up) {
        upstreamNodesMeta.push_back(up);
        upstream_nodes_count++;
    }

    void addDownstreamNode(const StreamMeta &down) {
        downstreamNodesMeta.push_back(down);
        downstream_nodes_count++;
    }

    // how many bytes will cost if we write this node information to file.
    unsigned long lenInfile()const {
        return sizeof(node_id) + sizeof(upstream_nodes_count) + sizeof(downstream_nodes_count) +
               sizeof(StreamMeta) * (upstreamNodesMeta.size() + downstreamNodesMeta.size());
        // todo more meta data.
    }

protected:
    std::vector<StreamMeta> upstreamNodesMeta;
    std::vector<StreamMeta> downstreamNodesMeta;

    _type_nodes_count downstream_nodes_count; // usually equals to 0 or 1.
    _type_nodes_count upstream_nodes_count;
};

#endif //PNOHS_D_NODE_H