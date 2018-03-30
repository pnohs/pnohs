//
// Created by genshen on 3/30/18.
//

#ifndef PNOHS_NODE_PARSE_H
#define PNOHS_NODE_PARSE_H


#include <utils/data_def.h>
#include <vector>
#include "partition_type.h"
#include "../graph/stream_meta.h"


class NodeParse {
public:
    _type_node_id node_id;

    std::vector<StreamMeta> upstreamNodesMeta;
    std::vector<StreamMeta> downstreamNodesMeta;

    // initial fs.
    NodeParse(std::fstream &fs, long base_offset);

    void parse();

private:
    std::fstream &fs;
    long base_offset; // base offset on this node.

    _type_nodes_count downstream_nodes_count; // usually equals to 0 or 1.
    _type_nodes_count upstream_nodes_count;

    /**
    * calculate relative offset by the offset to data position of this processor.
    * @param offset
    * @return relative offset.
    */
    inline long relativeOffset(long offset) {
        return base_offset + offset - fs.tellg();
    }

};


#endif //PNOHS_NODE_PARSE_H
