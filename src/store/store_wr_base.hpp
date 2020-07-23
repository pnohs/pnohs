//
// Created by genshen on 2020/7/23.
//

#ifndef PNOHS_STORE_WR_BASE_HPP
#define PNOHS_STORE_WR_BASE_HPP

#include "store_define.h"

/**
* base class for store read and write
* @tparam TID type of block id
* @tparam size_of_block size in bytes of block data
*/
template<typename TID, std::size_t size_of_block>
class StoreWRBase {
public:
    typedef store::BlockMeta<TID> _type_block_metadata;
    typedef std::vector<_type_block_metadata> _type_vec_block_meta;

    // the size of bytes for each block (for writer it is const, for reader its variable).
    store::_type_block_size block_size = size_of_block;
    // the total number of blocks (for writer it is const, for reader its variable).
    store::_type_block_num block_num;

    explicit StoreWRBase(const store::_type_block_num block_num) : block_num(block_num) {}

protected:

    /**
     * \return the offset from file begin to first data block.
     * or size of header part.
     */
    inline store::_type_data_cursor headerSize() {
        // metadata size + block num + block size
        return sizeof(_type_block_metadata) * block_num + sizeof(block_num) + sizeof(block_size);
    }

    /**
     * get absolute offset in file for begin for {block_index}th block data.
     * \param block_index the index of block. We are going to write {block_index}th block.
     * \return the offset we should move when using std::ios_base::beg (from file beginning) to write file.
     */
    inline store::_type_data_cursor blockDataOffset(store::_type_block_num block_index) {
        return headerSize() + block_size * block_index;
    }
};

#endif //PNOHS_STORE_WR_BASE_HPP
