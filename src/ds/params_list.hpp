//
// Created by genshen on 8/14/18.
//

#ifndef PNOHS_PARAMS_LIST_H
#define PNOHS_PARAMS_LIST_H


#include <array>
#include <map>
#include "base_data_list.hpp"

/**
 * Due to almost the types of model parameters are double,
 * so the first type of @memberof data is param_const.
 * @tparam N the size/count of model parameters.
 * @tparam ID unique id of the parameter list.
 *
 * @note: the @tparam ID must be different for different model parameters list.
 * Because the static member, keys, will be shared for all model param lists with the same @tparam N
 * if the @tparam ID is the same, which may cause unexpected behavior.
 * And more, if you create two different model parameters lists with the same @tparam ID and set keys for both lists,
 * it will raise a compiling error.
 */
template<std::size_t N, unsigned long ID>
class ParamsList : public BaseDataList<param_const, N> {
public:
    /**
     * the metadata of model parameters, including parameter key(or name),
     * max and min value, type of parameter.
     */
    static const std::array<param_meta, N> metadata_list;

    /**
     * id of of this parameter list.
     */
    static const unsigned long id = ID;

    /**
     * type of iterator of parameter map.
     */
    typedef typename std::map<std::string, param_const>::const_iterator tp_params_map_itl;

    static size_t getParamsSize();

    /**
     * fill array of parameters keys.
     * @param keys returned parameters keys.
     */
    static void getKeys(std::string keys[]);

    /**
     * assign values by a map, whose key is params key (or name) and value is params value.
     * @param
     */
    void setValuesMap(const std::map<std::string, param_const> &params_map);
};

template<size_t N, unsigned long ID>
size_t ParamsList<N, ID>::getParamsSize() {
    return N;
}

template<size_t N, unsigned long ID>
void ParamsList<N, ID>::getKeys(std::string keys[]) {
    // loop over metadata_list to fill keys array.
    for (size_t i = 0; i < N; ++i) {
        keys[i] = metadata_list[i].key;
    }
}

template<size_t N, unsigned long ID>
void ParamsList<N, ID>::setValuesMap(const std::map<std::string, param_const> &params_map) {
    for (tp_params_map_itl itl = params_map.begin(); itl != params_map.end(); ++itl) {
        for (size_t i = 0; i < N; ++i) {
            if (metadata_list[i].key == itl->first) {
                BaseDataList<param_const, N>::data[i] = itl->second;
                break;
            }
        }
    }
}

#endif //PNOHS_PARAMS_LIST_H
