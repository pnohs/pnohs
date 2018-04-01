//
// Created by genshen on 2018-03-31.
//

#include <fstream>
#include <iostream>
#include <json.hpp>
#include <io/io_utils.hpp>
#include <dispatch/dispatch_parse.h>
#include <dispatch/dispatch_writer.h>

void convertToBinary();

void convertToText();

using json = nlohmann::json;

int main() {
//    convertToBinary();
    convertToText();
    return 0;
}

void convertToText() {
    DispatchParse *pa = new DispatchParse("../../example/dispatch.dis", 1);
    pa->locate();
    NodeParse *np;
    while ((np = pa->nextNode()) != nullptr) {
        std::cout << "id: " << np->node_id << std::endl;
        std::cout << "upstream: " << std::endl;
        for (const StreamMeta &s:np->getUpstreamNodes()) {
            std::cout << "id: " << s.id << " locate: " << s.location << std::endl;
        }
        std::cout << "downstream: " << std::endl;
        for (const StreamMeta &s:np->getDownstreamNodes()) {
            std::cout << "id: " << s.id << " locate: " << s.location << std::endl;
        }
        std::cout << "end of node " << np->node_id << std::endl << std::endl;
    }
}

void convertToBinary() {
    std::ifstream is("../../example/dispatch.json"); // todo file name from argv.
    json json;
    is >> json;

    // todo file name from argv.
    std::fstream fs("../../example/dispatch.dis", std::ios::out | std::ios::binary);

    // todo parse header.
    kiwi::RID ranks = json["header"]["ranks"];
    _type_dispatch_fileoffset cursor_in_file = DispatchWriter::stat(ranks);
    int rank_i = 0;
    for (auto &rank_dispatch : json["dispatch"]) { // for each processors/randId
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
        }
        disWriter.postWrite(&cursor_in_file);
        rank_i++;
    }
    // todo write processors.
}
/**
//    _type_dispatch_fileoffset rank_offset_in_file = sizeof(kiwi::RID) + sizeof(_type_dispatch_fileoffset) * ranks;
//    int rank_i = 0;
//    for (auto &rank_dispatch : json["dispatch"]) { // for each processors/randId
//        kiwi::RID rank_id = rank_dispatch["rank_id"];
//        _type_nodes_count nodes_count = rank_dispatch["nodes_count"];
//        // length of header of this rank
//        _type_dispatch_fileoffset offset_in_rank = sizeof(_type_nodes_count) + nodes_count * sizeof(_type_dispatch_fileoffset);
//        int node_i = 0;
//        for (auto &node : rank_dispatch["nodes"]) { // for each nodes on each processors.
//            // move pointer to the start of this node data.
//            NodeParse *dp = new NodeParse(fs, rank_offset_in_file + offset_in_rank);
//            dp->node_id = node["node_id"];
//            for (auto downstream : node["downstream"]) { // for each downstream node of each node
//                StreamMeta downNode;
//                downNode.id = downstream["node_id"];
//                downNode.location = downstream["locate"];
//                dp->addDownstreamNode(downNode);
//            }
//            for (auto upstream : node["upstream"]) { // for each upstream node of each node
//                StreamMeta upNode;
//                upNode.id = upstream["node_id"];
//                upNode.location = upstream["locate"];
//                dp->addUpstreamNode(upNode);
//            }
//            dp->out(); // write data of this node to file.
//            // write this relative offset/index of node. relative offset means it is the offset in this rank.
//            kiwi::seekWrite(fs, &offset_in_rank,
//                            rank_offset_in_file + sizeof(_type_nodes_count) + node_i * sizeof(_type_dispatch_fileoffset),
//                            std::ios_base::beg, 1);
//            offset_in_rank += dp->lenInfile();
//            delete dp;
//            node_i++;
//        }
//        // write nodes count on this rank.
//        kiwi::seekWrite(fs, &nodes_count, rank_offset_in_file, std::ios_base::beg, 1);
//        // write ith rank dispatched nodes data offset.
//        kiwi::seekWrite(fs, &rank_offset_in_file,
//                        sizeof(kiwi::RID) + rank_i * sizeof(_type_dispatch_fileoffset),
//                        std::ios_base::beg, 1);
//        rank_offset_in_file += offset_in_rank;
//        rank_i
*/