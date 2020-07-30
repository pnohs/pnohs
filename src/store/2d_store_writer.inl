//
// Created by genshen on 2020/7/24.
//

#include <io/io_utils.hpp>
#include "2d_store_writer.hpp"

template<typename TID, typename T>
StoreWriter2D<TID, T>::StoreWriter2D(std::fstream &fs, store::_type_block_num block_num)
        :StoreWRBase<store::BlockMeta2D<TID>, sizeof(T)>(block_num), sfs(fs),
         block_num(block_num), cur_block_cursor(0), id_buffer() {
}

template<typename TID, typename T>
void StoreWriter2D<TID, T>::write(const TID id, const T *blocks, const store::_type_block_num sb_n) {
    kiwi::seekWrite(sfs, blocks, _type_wr2d_base::headerSize() + cur_block_cursor, std::ios_base::beg, sb_n);
    typename _type_wr2d_base::_type_block_metadata data{id, sb_n, cur_block_cursor};
    id_buffer.emplace_back(data);
    // increase cursor
    blocks_written++;
    cur_block_cursor += sb_n * sizeof(T);
}

template<typename TID, typename T>
void StoreWriter2D<TID, T>::done() {
    // write number of blocks
    kiwi::seekWrite(sfs, &(_type_wr2d_base::block_num), 0, std::ios_base::beg, 1);
    // also write sub block size
    kiwi::seekWrite(sfs, &(_type_wr2d_base::block_size), 0, std::ios_base::cur, 1);

    // write metadata of blocks
    assert(blocks_written == _type_wr2d_base::block_num); // make sure all expected data is written
    // sort before writing
    sort(id_buffer.begin(), id_buffer.end(), store::lessBlockMeta2DSort<TID>);
    kiwi::seekWrite(sfs, id_buffer.data(), 0, std::ios_base::cur, _type_wr2d_base::block_num);
}
