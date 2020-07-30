//
// Created by genshen on 2020/7/24.
//

#ifndef PNOHS_STORE_UTILS_HPP
#define PNOHS_STORE_UTILS_HPP

#include <cstdlib>

/**
 * binary search in an array of element type \tparam T .
 * And return the index of matched element in array.
 *
 * @tparam TID type of id
 * @tparam T type of element in search array
 * @param id the search id we expected to found
 * @param id_map the array for search
 * @param length the length of array
 * @return the index of matched element in array. If not found, @param length will be returned.
 */
template<typename TID, typename T>
std::size_t binarySearchById(const TID id, const T *id_map, const std::size_t length) {
    if (length == 0) {
        return length;
    }
    std::size_t p = 0;
    std::size_t r = length - 1;
    std::size_t q = (r + p) / 2;
    while (p <= r) {
        if (id_map[q].id == id)
            return q;
        else {
            if (id_map[q].id < id) {
                p = q + 1;
                q = (r + p) / 2;
            } else {
                r = q - 1;
                q = (r + p) / 2;
            }
        }
    }
    return length;
}


#endif //PNOHS_STORE_UTILS_HPP
