//
// Created by genshen on 4/1/18.
//

#ifndef PNOHS_DISPATCH_WRITER_H
#define PNOHS_DISPATCH_WRITER_H

#include <utils/data_def.h>
#include <string>
#include <fstream>
#include "dispatch_type.h"
#include "node_parse.h"

/**
 * write dispatch nodes data to file, including index information
 */
class DispatchWriter {
public:
    /** Initialize writer.
     * @param fs file stream for writer
     * @param offset_cursor writer data starting from this offset.
     */
    DispatchWriter(std::fstream &fs, _type_dispatch_file_offset offset_cursor, const _type_dispatch_rank_id rankId);

    /**
     * todo rename function name
     * stat writes rank_count to stream header, and initializes offset_course pointed to the first rank's dispatch data offset.
     * @param rank_count all ranks/processors.
     * @return file pointer, the cursor of initialized absolute offset.
     */
    static _type_dispatch_file_offset stat(const _type_dispatch_rank_id rank_count);

    /**
     * locate write node count to file stream and initialize @var offset_in_rank.
     * @param nodes_count
     */
    void locate(_type_dispatch_nodes_count nodes_count);

    /**
     * postWrite write index of this processor's dispatch data to file stream.
     * this function is called after all nodes has been written to file stream.
     * @return how many bytes of data of nodes dispatched to this rank.
     */
    _type_dispatch_file_offset postWrite(_type_dispatch_file_offset *cursor);

    /**
     * write a node data dispatched to this processor to file stream, as well as the node relative index.
     * @param np node data with its upstream and downstream meta data.
     */
    void write(const DNode *np);

private:
    _type_dispatch_nodes_count node_i = 0;
    _type_dispatch_rank_id rankId;
    // base offset in file, we then write nodes data of this rank from this offset.
    // we may modify this offset after finishing writing.
    const _type_dispatch_file_offset base_offset;
    // default is the space size of nodes count plus size of node indexes.
    _type_dispatch_file_offset offset_in_rank;

    std::fstream &ofs; // file stream for output.
};


#endif //PNOHS_DISPATCH_WRITER_H
