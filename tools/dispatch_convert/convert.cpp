//
// Created by genshen on 3/31/18.
//

#include "convert.h"
#include "ahct.h"

void convert::convertToText(const std::string disBinPath, const std::string disTextPath) {
    DispatchParse *pa = new DispatchParse(disBinPath, 1);  // todo 需要将所有处理器上的任务划分节点数据都写入到JSON文本中去，而不是单个的
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
    delete pa;
}

void convert::convertToBinary(std::string disTextPath, std::string disBinPath) {
    //using json = nlohmann::json;
    std::ifstream is(disTextPath);
    if (!is.good())
    {
        std::cerr << "open file " << disTextPath << " failed!" << std::endl;
    }
    nlohmann::json json;
    is >> json;

    std::fstream fs(disBinPath, ahct::MODE_OPEN_DIS_BIN_FILE4WRITING);

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
            delete dp;
        }
        disWriter.postWrite(&cursor_in_file);
        rank_i++;
    }
    // todo write processors.

    is.close();
    fs.close();
}
