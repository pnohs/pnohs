//
// Created by genshen on 2020/7/24.
//

#ifndef PNOHS_2D_STORE_READER_HPP
#define PNOHS_2D_STORE_READER_HPP

#include <fstream>
#include <vector>
#include "store_define.h"
#include "store_wr_base.hpp"

/**
 * In 2D store, each block can be divided into many sub-blocks.
 * @tparam TID type of block id
 * @tparam T the type for each sub block
 */
template<typename TID, typename T>
class StoreReader2D : public StoreWRBase<store::BlockMeta2D<TID>, sizeof(T)> {
public:
    typedef store::BlockMeta2D<TID> block_meta;
    typedef StoreWRBase<store::BlockMeta2D<TID>, sizeof(T)> _type_wr2d_base;

    /**
     * Initialize reader with file stream
     * @param fs the file for reading
     */
    explicit StoreReader2D(std::fstream &fs);

    /**
     *
     * @return number of blocks in file.
     */
    store::_type_block_size getBlockCount();

    /**
     * get metadata of a block by block id
     * \param block_id block id
     * \return metadata of the block specified by the block id
     */
    block_meta getBlockMeta(TID block_id);

    /**
     * read data block by the specified id.
     * @param id id of data block
     * @param data the result data block just read.
     * // fixme: we dont known the size of sub block before calling
     */
    void read(TID id, T *data);

private:
    // file stream for storage.
    std::fstream &sfs;
    // the map of block id and map storage index (or called block metadata).
    typename _type_wr2d_base::_type_vec_block_meta id_map;

};


#include "2d_store_reader.inl"

#endif //PNOHS_2D_STORE_READER_HPP
