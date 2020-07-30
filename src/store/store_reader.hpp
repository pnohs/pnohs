//
// Created by genshen on 2020/7/23.
//

#ifndef PNOHS_STORE_READER_HPP
#define PNOHS_STORE_READER_HPP

#include <fstream>
#include <vector>
#include "store_define.h"

/**
 *
 * @tparam TID type of block id
 * @tparam T the type for each block
 */
template<typename TID, typename T>
class StoreReader : public StoreWRBase<store::BlockMeta<TID>, sizeof(T)> {
public:
    typedef StoreWRBase<store::BlockMeta<TID>, sizeof(T)> _type_wr_base;

    /**
     * Initialize reader with file stream
     * @param fs the file for reading
     */
    explicit StoreReader(std::fstream &fs);

    /**
     *
     * @return number of blocks in file.
     */
    store::_type_block_size getBlockCount();

    /**
     * To check whether a block specified by id exists in this store file,
     * by searching metadata of blocks in header.
     * @param id the block id to search
     * @return true for existence, otherwise, return false.
     */
    bool isBlockExist(const TID id);

    /**
     * read data block by the specified id.
     * @param id id of data block
     * @param data the result data block just read.
     */
    void read(const TID id, T *data);

private:
    // file stream for storage.
    std::fstream &sfs;
    // the map of block id and map storage index (or called block metadata).
    std::vector<store::BlockMeta<TID>> id_map;
};

#include "store_reader.inl"

#endif //PNOHS_STORE_READER_HPP
