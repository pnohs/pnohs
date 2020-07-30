//
// Created by genshen on 8/14/18.
//

#ifndef PNOHS_PARAMS_LIST_H
#define PNOHS_PARAMS_LIST_H


#include <array>
#include <map>
#include "data_list_with_meta.hpp"

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
class ParamsList : public DataListWithMeta<param_const, N, ID, param_meta> {
public:
    typedef DataListWithMeta<param_const, N, ID, param_meta> base_type_with_meta;
    typedef typename DataListWithMeta<param_const, N, ID, param_meta>::_type_raw_data_list _type_raw_param_list;

    static size_t getParamsSize();
};

template<std::size_t N, unsigned long ID>
size_t ParamsList<N, ID>::getParamsSize() {
    return N;
}

#endif //PNOHS_PARAMS_LIST_H
