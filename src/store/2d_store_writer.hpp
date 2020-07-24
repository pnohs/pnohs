//
// Created by genshen on 2020/7/24.
//

#ifndef PNOHS_2D_STORE_WRITER_HPP
#define PNOHS_2D_STORE_WRITER_HPP

#include <fstream>
#include <vector>
#include "store_define.h"
#include "store_wr_base.hpp"

/**
 * In 2D store, each block can be divided into many sub-blocks.
 * Thus, we should record the number of sub-blocks in each block.
 * @tparam TID type of block id
 * @tparam T the type of sub block
 */
template<typename TID, typename T>
class StoreWriter2D : public StoreWRBase<store::BlockMeta2D<TID>, sizeof(T)> {
public:
    typedef store::BlockMeta2D<TID> block_meta;
    typedef StoreWRBase<store::BlockMeta2D<TID>, sizeof(T)> _type_wr2d_base;

    /**
     * Initialize writer with file stream and blocks number
     * @param fs the file for writing data
     * @param block_num the number of writing blocks
     */
    StoreWriter2D(std::fstream &fs, const store::_type_block_num block_num);

    /**
     * write a block into file
     * @param id  block id for the data block to be written
     * @param block the pointer of data block
     * @param sb the number of sub-blocks for this block
     */
    void write(const TID id, const T *blocks, const store::_type_block_num sb_n);

    /**
     * do post works of file writing (e.g. write header).
     */
    void done();

private:
    // file stream for writing.
    std::fstream &sfs;
    const store::_type_block_num block_num = 0;

    /**
     * the cursor in file for writing next data block (starting from the first data block).
     */
    store::_type_data_cursor cur_block_cursor;

    /**
     * id buffer for latter writing into file header
     */
    typename _type_wr2d_base::_type_vec_block_meta id_buffer;
    store::_type_block_num blocks_written = 0;
};


#include "2d_store_writer.inl"

#endif //PNOHS_2D_STORE_WRITER_HPP
