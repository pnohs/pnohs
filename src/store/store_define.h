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
}

#endif //PNOHS_STORE_DEFINE_H
