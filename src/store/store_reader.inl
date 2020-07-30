//
// Created by genshen on 2020/7/23.
//

#include <io/io_utils.hpp>
#include "store_reader.hpp"
#include "store_utils.hpp"


template<typename TID, typename T>
StoreReader<TID, T>::StoreReader(std::fstream &fs): StoreWRBase<store::BlockMeta<TID>, sizeof(T)>(0), sfs(fs) {
    // read block number and block size
    kiwi::seekRead(fs, &(_type_wr_base::block_num), 0, std::ios_base::beg, 1);
    kiwi::seekRead(fs, &(_type_wr_base::block_size), 0, std::ios_base::cur, 1);
    assert(_type_wr_base::block_num >= 0);
    assert(_type_wr_base::block_size == sizeof(T));

    // load block metadata (id map) in header
    id_map.resize(_type_wr_base::block_num);
    kiwi::seekRead(sfs, id_map.data(), sizeof(_type_wr_base::block_num) + sizeof(_type_wr_base::block_size),
                   std::ios_base::beg, _type_wr_base::block_num);
    // sort to make sure
    sort(id_map.begin(), id_map.end(), store::lessBlockMetaSort<TID>);
}

template<typename TID, typename T>
store::_type_block_size StoreReader<TID, T>::getBlockCount() {
    return _type_wr_base::block_num;
}

template<typename TID, typename T>
void StoreReader<TID, T>::read(TID id, T *data) {
    store::_type_block_num index = binarySearchById<TID, typename _type_wr_base::_type_block_metadata>(
            id, id_map.data(), _type_wr_base::block_num);
    if (index == _type_wr_base::block_num) {
        throw std::runtime_error("not found");
    }
    kiwi::seekRead(sfs, data, _type_wr_base::offsetWithFixedBlockSize(id_map[index].index), std::ios_base::beg, 1);
}

template<typename TID, typename T>
bool StoreReader<TID, T>::isBlockExist(const TID id) {
    return binarySearchById<TID, typename _type_wr_base::_type_block_metadata>(
            id, id_map.data(), _type_wr_base::block_num) != _type_wr_base::block_num;
}
