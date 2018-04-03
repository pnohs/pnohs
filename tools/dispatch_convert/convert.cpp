//
// Created by genshen on 3/31/18.
//

#include <io/io_utils.hpp>
#include "convert.h"
#include "ahct.h"

void convert::convertToText(const std::string disBinPath, const std::string disTextPath) {

    std::fstream fs = std::fstream(disBinPath, ahct::MODE_OPEN_DIS_BIN_FILE4READING);
    if (!fs.good()) {
        std::cerr << "open file " << disBinPath << " failed!" << std::endl;
        return;
    }

    std::fstream ofs = std::fstream(disTextPath, ahct::MODE_OPEN_DIS_TEXT_FILE4WRITING);
    if (!ofs.good()) {
        std::cerr << "open file " << disTextPath << " failed!" << std::endl;
        return;
    }

    nlohmann::json json;

    // get processor count
    kiwi::RID ranks;
    kiwi::seekRead(fs, &ranks, 0, std::ios_base::beg, 1);



    json["dispatch"] = nlohmann::json::array();
    json["header"] = nlohmann::json::object();
    json["header"]["ranks"] = ranks;

    for (int rank_i = 0; rank_i < ranks; rank_i++)
    {
        nlohmann::json json_rank_i;
        nlohmann::json json_rank_i_nodes = nlohmann::json::array();

        int node_count = 0;

        DispatchParse *pa = new DispatchParse(fs, rank_i);  // todo 需要将所有处理器上的任务划分节点数据都写入到JSON文本中去，而不是单个的
        pa->locate();

        DNode node;
        while (pa->isAfterLast()) {

            nlohmann::json json_rank_i_node = nlohmann::json::object();
            nlohmann::json json_rank_i_node_upstream = nlohmann::json::array();
            nlohmann::json json_rank_i_node_downstream = nlohmann::json::array();

            node = pa->nextNode();

            for (const StreamMeta &s:node.getUpstreamNodes()) {
                nlohmann::json upstreamNode = nlohmann::json::object();
                upstreamNode["node_id"] = s.id;
                upstreamNode["locate"] = s.location;
                json_rank_i_node_upstream.push_back(upstreamNode);
            }

            for (const StreamMeta &s:node.getDownstreamNodes()) {
                nlohmann::json downstreamNode = nlohmann::json::object();
                downstreamNode["node_id"] = s.id;
                downstreamNode["locate"] = s.location;
                json_rank_i_node_downstream.push_back(downstreamNode);
            }

            node_count ++;

            json_rank_i_node["downstream"] = json_rank_i_node_downstream;
            json_rank_i_node["upstream"] = json_rank_i_node_upstream;
            json_rank_i_node["node_id"] = node.node_id;

            json_rank_i_nodes.push_back(json_rank_i_node);
        }

        json_rank_i["rank_id"] = rank_i;
        json_rank_i["nodes_count"] = node_count;
        json_rank_i["nodes"] = json_rank_i_nodes;

        json["dispatch"].push_back(json_rank_i);

        delete pa;
    }


    ofs << std::setw(4) << json << std::endl;

    fs.close();
    ofs.close();
}

void convert::convertToBinary(std::string disTextPath, std::string disBinPath) {

    std::ifstream is(disTextPath);
    if (!is.good()) {
        std::cerr << "open file " << disTextPath << " failed!" << std::endl;
        return;
    }

    nlohmann::json json;
    is >> json;

    std::fstream fs(disBinPath, ahct::MODE_OPEN_DIS_BIN_FILE4WRITING);
    if (!fs.good()) {
        std::cerr << "open file " << disTextPath << " failed!" << std::endl;
        return;
    }

    // todo parse header.
    kiwi::RID ranks = json["header"]["ranks"];
    _type_dispatch_fileoffset cursor_in_file = DispatchWriter::stat(ranks); // todo stat函数中未将ranks写入文件
    kiwi::seekWrite(fs, &ranks, 0, std::ios_base::beg, 1); // todo stat完善后需删除

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
        kiwi::seekWrite(fs, &cursor_in_file, sizeof(ranks) + rank_i * sizeof(cursor_in_file),
                        std::ios_base::beg, 1); // todo 写入各进程的划分数据在输入文件中的base_offset
        disWriter.postWrite(&cursor_in_file);
        rank_i++;
    }
    // todo write processors.

    is.close();
    fs.close();
}
