//
// Created by genshen on 2020/7/23.
//

#ifndef PNOHS_STORE_DEFINE_H
#define PNOHS_STORE_DEFINE_H

#include <cstdlib>

namespace store {
    template<typename TID>
    struct BlockMeta {
        TID id;
        std::size_t index;
    };

    template<typename TID>
    inline bool lessBlockMetaSort(struct BlockMeta<TID> a, struct BlockMeta<TID> b) { return a.id < b.id; }

    // type of offset/cursor in file
    typedef std::size_t _type_data_cursor;
    typedef _type_data_cursor _type_block_size;
    typedef std::size_t _type_block_num;

    template<typename TID>
    struct BlockMeta2D {
        TID id;
        _type_block_num sub_blocks_num;
        _type_data_cursor cursor;
    };

    template<typename TID>
    inline bool lessBlockMeta2DSort(struct BlockMeta2D<TID> a, struct BlockMeta2D<TID> b) { return a.id < b.id; }

}

#endif //PNOHS_STORE_DEFINE_H
