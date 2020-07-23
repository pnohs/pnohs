//
// Created by genshen on 2020/7/18.
//

#ifndef PNOHS_STORE_WRITER_HPP
#define PNOHS_STORE_WRITER_HPP

#include <fstream>
#include <vector>
#include "store_define.h"
#include "store_wr_base.hpp"

/**
 *
 * @tparam TID type of block id
 * @tparam T the type for each block
 */
template<typename TID, typename T>
class StoreWriter : public StoreWRBase<TID, sizeof(T)> {
public:
    typedef StoreWRBase<TID, sizeof(T)> _type_wr_base;

    /**
     * Initialize writer with file stream and blocks number
     * @param fs the file for writing data
     * @param block_num the number of writing blocks
     */
    StoreWriter(std::fstream &fs, const store::_type_block_num block_num);

    /**
     * write block(s) into file system
     * @param ids  blocks id for each data block to be written
     * @param blocks the data blocks
     * @param n the number of blocks
     */
    void write(const TID *ids, const T *blocks, store::_type_block_num n);

    /**
     * do post works of file writing (e.g. write header).
     */
    void done();
    // todo we can use buffer for writing

private:
    store::_type_block_num blocks_written = 0;
    // file stream for storage.
    std::fstream &sfs;

    typename _type_wr_base::_type_vec_block_meta id_buffer;

    /**
     * write the header data: including the number of block, block data size, metadata of block data
     */
    void writeHeader();
};

#include "store_writer.inl"

#endif //PNOHS_STORE_WRITER_HPP
