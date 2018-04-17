//
// Created by genshen on 3/28/18.
//

#include <cassert>

#include <io/io_utils.hpp>
#include "dispatch_parse.h"

DispatchParse::DispatchParse(std::fstream &dispatchStream, const _type_dispatch_rank_id processorId) :
        fs(dispatchStream), rid(processorId) {}

void DispatchParse::locate() {
    // 读取本进程所需子流域数据在输入文件中的最开始偏移量
    kiwi::seekRead(fs, &base_offset, sizeof(_type_dispatch_rank_id) + rid * sizeof(_type_dispatch_file_offset),
                   std::ios_base::beg, 1); // locate to the position of data index.
    assert(base_offset >= 0); // todo if

    // 读取本进程需要模拟的总子流域数目
    kiwi::seekRead(fs, &nodes_count, base_offset, std::ios_base::beg, 1);
    assert(nodes_count >= 0);
}

void DispatchParse::locateNode(_type_dispatch_node_index index) {
    _type_dispatch_file_offset node_offset = 0; // use node offset to locate where the ith node is.

    // get relative offset in file of ith node.
    // re_offset is the offset from base_offset (absolute offset to data location of this processor) to [ith node index].
    long re_offset = sizeof(nodes_count) + index * sizeof(_type_dispatch_file_offset); // todo header is nodes_count.
    kiwi::seekRead(fs, &node_offset, relativeOffset(re_offset), std::ios_base::cur, 1);
    assert(node_offset >= 0);

    fs.seekg(relativeOffset(node_offset), std::ios_base::cur); // seek to node date location.
}

const DNode DispatchParse::nextNode() {
    if (current_node_index < nodes_count) {
        locateNode(current_node_index);
        NodeParse np = NodeParse(fs, fs.tellg()); // todo remember to delete.
        np.parse();
        current_node_index++;
        return np;
    }
    return DNode();
}
