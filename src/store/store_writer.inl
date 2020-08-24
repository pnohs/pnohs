//
// Created by genshen on 2020/7/18.
//

#include <cassert>
#include <algorithm>
#include <io/io_utils.hpp>
#include "store_writer.hpp"

template<typename TID, typename T>
StoreWriter<TID, T>::StoreWriter(std::fstream &fs, const store::_type_block_num block_num)
        : StoreWRBase<store::BlockMeta<TID>, sizeof(T)>(block_num), sfs(fs), id_buffer() {
}

template<typename TID, typename T>
void StoreWriter<TID, T>::writeHeader() {
    // write number of blocks
    kiwi::seekWrite(sfs, &(_type_wr_base::block_num), 0, std::ios_base::beg, 1);
    // also write block size
    kiwi::seekWrite(sfs, &(_type_wr_base::block_size), 0, std::ios_base::cur, 1);

    // write metadata of blocks
    assert(blocks_written == _type_wr_base::block_num); // make sure all expected data is written
    // sort before writing
    std::sort(id_buffer.begin(), id_buffer.end(), store::lessBlockMetaSort<TID>);
    kiwi::seekWrite(sfs, id_buffer.data(), 0, std::ios_base::cur, _type_wr_base::block_num);
}

template<typename TID, typename T>
void StoreWriter<TID, T>::write(const TID *ids, const T *blocks, store::_type_block_num n) {
    // we are going to write {blocks_written}th blocks
    // block (0,1,2,.. blocks_written-1) have been written.
    kiwi::seekWrite(sfs, blocks, _type_wr_base::offsetWithFixedBlockSize(blocks_written) - sfs.tellg(), std::ios_base::cur, n);
    // buffer block ids
    for (store::_type_block_num i = 0; i < n; i++) {
        typename _type_wr_base::_type_block_metadata data  {ids[i], blocks_written + i};
        id_buffer.emplace_back(data);
    }
    // increase blocks number we have written
    blocks_written += n;
}

template<typename TID, typename T>
void StoreWriter<TID, T>::done() {
    writeHeader();
}
