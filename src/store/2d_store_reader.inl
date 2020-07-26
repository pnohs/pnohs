//
// Created by genshen on 2020/7/24.
//

#include <io/io_utils.hpp>
#include "2d_store_reader.hpp"
#include "store_utils.hpp"

template<typename TID, typename T>
StoreReader2D<TID, T>::StoreReader2D(std::fstream &fs): StoreWRBase<store::BlockMeta2D<TID>, sizeof(T)>(0), sfs(fs) {
    // read block number and sub-block size
    kiwi::seekRead(fs, &(_type_wr2d_base::block_num), 0, std::ios_base::beg, 1);
    kiwi::seekRead(fs, &(_type_wr2d_base::block_size), 0, std::ios_base::cur, 1);
    assert(_type_wr2d_base::block_num >= 0);
    assert(_type_wr2d_base::block_size == sizeof(T));

    // load block metadata (id map) in header
    id_map.resize(_type_wr2d_base::block_num);
    kiwi::seekRead(sfs, id_map.data(), sizeof(_type_wr2d_base::block_num) + sizeof(_type_wr2d_base::block_size),
                   std::ios_base::beg, _type_wr2d_base::block_num);
    // sort to make sure
    sort(id_map.begin(), id_map.end(), store::lessBlockMeta2DSort<TID>);
}

template<typename TID, typename T>
store::_type_block_size StoreReader2D<TID, T>::getBlockCount() {
    return _type_wr2d_base::block_num;
}

template<typename TID, typename T>
void StoreReader2D<TID, T>::read(const TID id, T *data) {
    const block_meta meta = getBlockMeta(id);
    kiwi::seekRead(sfs, data, _type_wr2d_base::headerSize() + meta.cursor, std::ios_base::beg, meta.sub_blocks_num);
}

template<typename TID, typename T>
void StoreReader2D<TID, T>::read(const TID id, T *data, const std::size_t size) {
    const block_meta meta = getBlockMeta(id);
    store::_type_block_num read_sub_blocks_num = meta.sub_blocks_num;
    if (meta.sub_blocks_num >= size) {
        read_sub_blocks_num = size;
    }
    kiwi::seekRead(sfs, data, _type_wr2d_base::headerSize() + meta.cursor, std::ios_base::beg, read_sub_blocks_num);
}

template<typename TID, typename T>
typename StoreReader2D<TID, T>::block_meta StoreReader2D<TID, T>::getBlockMeta(const TID block_id) {
    store::_type_block_num index = binarySearchById<TID, typename _type_wr2d_base::_type_block_metadata>(
            block_id, id_map.data(), _type_wr2d_base::block_num);
    if (index == _type_wr2d_base::block_num) {
        throw std::runtime_error("not found");
    }
    return id_map[index];
}
