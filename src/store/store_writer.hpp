//
// Created by genshen on 2020/7/18.
//

#ifndef PNOHS_STORE_WRITER_HPP
#define PNOHS_STORE_WRITER_HPP

#include <fstream>
#include <vector>
#include "store_define.h"

/**
 *
 * @tparam TID type of block id
 * @tparam T the type for each block
 */
template<typename TID, typename T>
class StoreWriter {
public:
    typedef store::BlockMeta<TID> _type_block_metadata;

    /**
     * Initialize writer with file stream and blocks number
     * @param fs the file for writing data
     * @param block_num the number of writing blocks
     */
    StoreWriter(std::fstream &fs, store::_type_block_num block_num);

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
    // the size of bytes for each block
    const store::_type_block_size block_size;
    // the total number of blocks
    const store::_type_block_num block_num;
    store::_type_block_num blocks_written = 0;
    // file stream for storage.
    std::fstream &sfs;

    std::vector<_type_block_metadata> id_buffer;

    /**
     * write the header data: including the number of block, block data size, metadata of block data
     */
    void writeHeader();

    /**
     * \return the offset from file begin to first data block.
     */
    inline store::_type_data_cursor firstBlockOffset() {
        // metadata size + block num + block size
        return sizeof(_type_block_metadata) * block_num + sizeof(store::_type_block_num) +
               sizeof(store::_type_block_size);
    }

    /**
     * when writing data using std::ios_base::cur, we must known the relative offset to current cursor.
     *
     * \param block_index the index of block. We are going to write {block_index}th block.
     * \return the offset we should move when using std::ios_base::cur to write file.
     */
    inline store::_type_data_cursor relativeOffset(store::_type_block_num block_index) {
        return firstBlockOffset() + sizeof(T) * block_index - sfs.tellg();
    }
};

#include "store_writer.inl"

#endif //PNOHS_STORE_WRITER_HPP
