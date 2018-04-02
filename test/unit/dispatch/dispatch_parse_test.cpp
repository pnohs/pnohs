//
// Created by genshen on 3/30/18.
//

#include <gtest/gtest.h>
#include <json.hpp>
#include <io/io_utils.hpp>
#include "../test_config.h"
#include "dispatch/dispatch_writer.h"
#include "dispatch/dispatch_parse.h"
#include "dispatch_json_string.h"

const std::string dispatch_bin_file = TEST_TEMP_STORAGE_PATH "/dispatch.bin";
const int ranks = 3;

void generateDispatchBinFile() {
    std::fstream fs(dispatch_bin_file, std::ios::out | std::ios::binary);
    auto dispatch_json = nlohmann::json::parse(DISPATCH_JSON);

    _type_dispatch_fileoffset cursor_in_file = DispatchWriter::stat(ranks);
    int rank_i = 0;
    for (auto &rank_dispatch : dispatch_json["dispatch"]) { // for each processors/randId
        // kiwi::RID rank_id = rank_dispatch["rank_id"];
        DispatchWriter disWriter = DispatchWriter(fs, cursor_in_file, rank_i); // or use rank_id from json
        _type_nodes_count nodes_count = rank_dispatch["nodes_count"];
        disWriter.locate(nodes_count);

        for (auto &node : rank_dispatch["nodes"]) { // for each nodes on each processors.
            // move pointer to the start of this node data.
            auto *dp = new DNode();
            dp->node_id = node["node_id"];
            for (auto downstream : node["downstream"]) { // for each downstream node of each node
                StreamMeta downNode{};
                downNode.id = downstream["node_id"];
                downNode.location = downstream["locate"];
                dp->addDownstreamNode(downNode);
            }
            for (auto upstream : node["upstream"]) { // for each upstream node of each node
                StreamMeta upNode{};
                upNode.id = upstream["node_id"];
                upNode.location = upstream["locate"];
                dp->addUpstreamNode(upNode);
            }
            disWriter.write(dp);
            delete dp;
        }
        disWriter.postWrite(&cursor_in_file);
        rank_i++;
    }
}

// todo NO MPI in this test.
// test node_id nad stream meta.
TEST(dispatch_parse_test_1, dispatch_parse_test) {
    generateDispatchBinFile();

    DispatchParse *pa = new DispatchParse(dispatch_bin_file, 0);
    pa->locate();
    NodeParse *np;
    np = pa->nextNode();

    EXPECT_EQ(np->node_id, 16);

    auto up_nodes = np->getUpstreamNodes(); // size = 4
    EXPECT_EQ(up_nodes[0].id, 1000);
    EXPECT_EQ(up_nodes[0].location, 2000);

    EXPECT_EQ(up_nodes[3].id, 1003);
    EXPECT_EQ(up_nodes[3].location, 2006);
    delete pa;
}

// test node count, and up/down stream count.
TEST(dispatch_parse_test_2, dispatch_parse_test) {
    generateDispatchBinFile();

    DispatchParse *pa = new DispatchParse(dispatch_bin_file, 1);
    pa->locate();
    NodeParse *np;

    np = pa->nextNode();
    EXPECT_EQ(np->getUpstreamNodesCount(), 4);
    EXPECT_EQ(np->getDownstreamNodesCount(), 1);

    np = pa->nextNode();
    EXPECT_EQ(np->getUpstreamNodesCount(), 0);
    EXPECT_EQ(np->getDownstreamNodesCount(), 1);

    EXPECT_EQ(pa->nextNode(), nullptr);

    delete pa;
}

// test empty node.
TEST(dispatch_parse_test_3, dispatch_parse_test) {
    generateDispatchBinFile();

    DispatchParse *pa = new DispatchParse(dispatch_bin_file, 2);
    pa->locate();
    EXPECT_EQ(pa->nextNode(), nullptr); // no nodes

    delete pa;
}