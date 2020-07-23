//
// Created by genshen on 2020/7/23.
//

#ifndef PNOHS_STORE_READER_HPP
#define PNOHS_STORE_READER_HPP

#include <fstream>
#include "store_define.h"

/**
 *
 * @tparam TID type of block id
 * @tparam T the type for each block
 */
template<typename TID, typename T>
class StoreReader {
public:
    /**
     * Initialize reader with file stream
     * @param fs the file for reading
     */
    StoreReader(std::fstream &fs);

    /**
     *
     * @return number of blocks in file.
     */
    store::_type_block_size getBlockCount();

    /**
     * read data block by the specified id.
     * @param id id of data block
     * @param data the result data block just read.
     */
    void read(TID id, T *data);

private:
    // the size of bytes for each block
    store::_type_block_size block_size;
    // the total number of blocks
    store::_type_block_num block_num;
    // file stream for storage.
    std::fstream &sfs;
    // the map of block id and map storage index (or called block metadata).
    std::vector<store::BlockMeta<TID>> id_map;

    /**
     * do binary search for a given id
     * \param id the given id
     * \param length the length of array/vector
     * \return the index of found id, if not found, length will be returned.
     */
    size_t id_map_binary_search(const TID id, const size_t length);
};

#include "store_reader.inl"

#endif //PNOHS_STORE_READER_HPP
