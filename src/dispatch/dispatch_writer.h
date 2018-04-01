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
    /** initial writer.
     * @param fs file stream for writer
     * @param offset_cursor writer data starting from this offset.
     */
    DispatchWriter(std::fstream &fs, _type_dispatch_fileoffset offset_cursor, const kiwi::RID rankId);

    /**
     * todo rename function name
     * stat write rank_count to stream header, and initial offset_course pointed to the first rank's dispatch data offset.
     * @param rank_count all ranks/processors.
     * @return file pointer, initialed absolute offset cursor
     */
    static _type_dispatch_fileoffset stat(const kiwi::RID rank_count);

    /**
     * locate write node count to file stream and initial variable offset_in_rank.
     * @param nodes_count
     */
    void locate(_type_nodes_count nodes_count);

    /**
     * postWrite write index of this processor's dispatch data to file stream.
     * this function is called after all nodes has been written to file stream.
     * @return how many bytes of data of nodes dispatched to this rank.
     */
    _type_dispatch_fileoffset postWrite(_type_dispatch_fileoffset *cursor);

    /**
     * write a node data dispatched to this processor to file stream, as well as the node relative index.
     * @param np node data with its upstream and downstream meta data.
     */
    void write(const DNode *np);

private:
    _type_nodes_count node_i = 0;
    kiwi::RID rankId;
    // base offset in file, we then write nodes data of this rank from this offset.
    // we may modify this offset after finishing writing.
    const _type_dispatch_fileoffset base_offset;
    // default is the space size of nodes count plus size of node indexes.
    _type_dispatch_fileoffset offset_in_rank;

    std::fstream &ofs; // file stream for output.
};


#endif //PNOHS_DISPATCH_WRITER_H
