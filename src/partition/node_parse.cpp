//
// Created by genshen on 3/30/18.
//

#include <io/io_utils.hpp>
#include <cassert>
#include "node_parse.h"

NodeParse::NodeParse(std::fstream &fs, long base_offset) :
        fs(fs), base_offset(base_offset),
        upstreamNodesMeta(), downstreamNodesMeta() {}

void NodeParse::parse() {
    // read count of upstream and downstream.
    kiwi::seekRead(fs, &node_id, 0, std::ios_base::cur, 1); // file pointer is just here,so offset if 0.
    kiwi::seekRead(fs, &downstream_nodes_count, 0, std::ios_base::cur, 1);
    kiwi::seekRead(fs, &upstream_nodes_count, 0, std::ios_base::cur, 1);
    assert(downstream_nodes_count >= 0);
    assert(upstream_nodes_count >= 0);

    // resize vector of stream.
    if (downstream_nodes_count > 0) { //
        // convert long to unsigned long
        downstreamNodesMeta.resize(downstream_nodes_count);
    }
    if (upstream_nodes_count > 0) { //
        // convert long to unsigned long
        upstreamNodesMeta.resize(static_cast<unsigned long>(upstream_nodes_count));
    }

    // read upstream and downstream metadata.
    kiwi::seekRead(fs, &downstreamNodesMeta[0], 0, std::ios_base::cur, downstream_nodes_count);
    kiwi::seekRead(fs, &upstreamNodesMeta[0], 0, std::ios_base::cur, upstream_nodes_count);
    // todo other meta info.
}
