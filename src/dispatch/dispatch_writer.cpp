//
// Created by genshen on 2018-04-01, April Fools' Day.
//

#include <io/io_utils.hpp>
#include "dispatch_writer.h"

DispatchWriter::DispatchWriter(std::fstream &fs, _type_dispatch_file_offset offset_cursor,
                               const _type_dispatch_rank_id rankId)
        : rankId(rankId), base_offset(offset_cursor), ofs(fs) {
}

_type_dispatch_file_offset DispatchWriter::stat(const _type_dispatch_rank_id rank_count) {
    // todo write rank count.
    return sizeof(rank_count) + sizeof(_type_dispatch_file_offset) * rank_count;
}

void DispatchWriter::locate(_type_dispatch_nodes_count nodes_count) {
    offset_in_rank = sizeof(_type_dispatch_nodes_count) + nodes_count * sizeof(_type_dispatch_file_offset);
    kiwi::seekWrite(ofs, &nodes_count, base_offset, std::ios_base::beg, 1); // write node count.
}

_type_dispatch_file_offset DispatchWriter::postWrite(_type_dispatch_file_offset *cursor) {
    kiwi::seekWrite(ofs, &base_offset,
                    sizeof(_type_dispatch_rank_id) + rankId * sizeof(_type_dispatch_file_offset),
                    std::ios_base::beg, 1);
    *cursor += offset_in_rank; // offset to next rank location in file.
    return offset_in_rank;
}

void DispatchWriter::write(const DNode *np) {
    // todo refuse writing if we have wrote more then [nodes_count] nodes.
    // write node data to binary file or fstream (including upstream and downstream metadata).
    _type_dispatch_nodes_count up_count = np->getUpstreamNodesCount();
    _type_dispatch_nodes_count down_count = np->getDownstreamNodesCount();

    ofs.seekg(base_offset + offset_in_rank, std::ios_base::beg); // seek to start position first.
    kiwi::seekWrite(ofs, &(np->node_id), 0, std::ios_base::cur, 1); // file pointer is just here,so offset if 0.
    kiwi::seekWrite(ofs, &down_count, 0, std::ios_base::cur, 1);
    kiwi::seekWrite(ofs, &up_count, 0, std::ios_base::cur, 1);

    // write upstream and downstream metadata.
    kiwi::seekWrite(ofs, &(np->getDownstreamNodes()[0]), 0, std::ios_base::cur, down_count);
    kiwi::seekWrite(ofs, &(np->getUpstreamNodes()[0]), 0, std::ios_base::cur, up_count);

    // write node index.
    kiwi::seekWrite(ofs, &offset_in_rank,
                    base_offset + sizeof(_type_dispatch_nodes_count) + node_i * sizeof(_type_dispatch_file_offset),
                    std::ios_base::beg, 1);
    node_i++;
    offset_in_rank += np->lenInfile(); // offset to next node location in file.
}
