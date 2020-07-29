//
// Created by genshen on 2020/7/29.
//

#ifndef PNOHS_DATA_LIST_WITH_META_HPP
#define PNOHS_DATA_LIST_WITH_META_HPP

#include <type_traits>
#include <cstdlib>
#include <map>
#include "base_data_list.hpp"

namespace ds {
    typedef std::string _type_metadata_key;
    typedef struct {
        _type_metadata_key key;
    } _type_data_meta;
}


/**
 * This class is based on BaseDataList with some extension.
 * It provide metadata for each data in list.
 *
 * User can also provide their metadata type, but the user customized metadata type must have a member `key` of string type.
 * User can set data list by keys in metadata.
 *
 * \tparam T type of data type in data list
 * \tparam N the data size in data list
 * \tparam ID ID of this metadata (metadata is stored as static, thus ID is here for generating unique class)
 * \tparam M type of metadata
 */
template<typename T, std::size_t N, unsigned long ID, typename M = ds::_type_data_meta>
class DataListWithMeta : public BaseDataList<T, N> {
    // assert existence
    static_assert(std::is_member_pointer<decltype(&M::key)>::value, "M must have a member `key` of string type");

public:
    /**
     * the metadata of model parameters, including parameter key(or name),
     * max and min value, type of parameter.
     */
    static const std::array<M, N> metadata_list;

    /**
     * id of of this parameter list.
     */
    static const unsigned long id = ID;

    /**
     * type of iterator of parameter map.
     */
    typedef typename std::map<ds::_type_metadata_key, T>::const_iterator tp_params_map_itl;

    /**
     * @return data size in data list
     */
    static size_t getDataSize();

    /**
     * fill array of parameters keys.
     * @param keys returned parameters keys.
     */
    static void getKeys(ds::_type_metadata_key keys[]);

    /**
     * assign values by a map, whose key is params key (or name) and value is params value.
     * @param
     */
    void setValuesMap(const std::map<ds::_type_metadata_key, T> &params_map);
};

template<typename T, std::size_t N, unsigned long ID, typename M>
size_t DataListWithMeta<T, N, ID, M>::getDataSize() {
    return N;
}

template<typename T, std::size_t N, unsigned long ID, typename M>
void DataListWithMeta<T, N, ID, M>::getKeys(ds::_type_metadata_key keys[]) {
    // loop over metadata_list to fill keys array.
    for (size_t i = 0; i < N; ++i) {
        keys[i] = metadata_list[i].key;
    }
}

template<typename T, std::size_t N, unsigned long ID, typename M>
void DataListWithMeta<T, N, ID, M>::setValuesMap(const std::map<params_key, T> &params_map) {
    for (const auto &itl : params_map) {
        for (size_t i = 0; i < N; ++i) {
            if (metadata_list[i].key == itl.first) {
                BaseDataList<T, N>::data[i] = itl.second;
                break;
            }
        }
    }
}

#endif //PNOHS_DATA_LIST_WITH_META_HPP
