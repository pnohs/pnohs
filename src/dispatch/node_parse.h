//
// Created by genshen on 3/30/18.
//

#ifndef PNOHS_NODE_PARSE_H
#define PNOHS_NODE_PARSE_H


#include <utils/data_def.h>
#include <vector>
#include "dispatch_type.h"
#include "../graph/stream_meta.h"
#include "dnode.hpp"


class NodeParse : public DNode {
public:

    // initial with fs for parsing.
    NodeParse(std::fstream &fs, long base_offset);

    // parse information about this node (including upstream and downstream metadata)
    // from dispatch binary file starting from base_offset.
    void parse();

private:
    std::fstream &fs;
    long base_offset; // absolute offset of this node from beginning of file, only used in parse.

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
