//
// Created by genshen on 8/14/18.
//

#ifndef PNOHS_PARAMS_LIST_H
#define PNOHS_PARAMS_LIST_H


#include "base_data_list.hpp"

/**
 * Due to almost the types of model parameters are double,
 * so the first type of @memberof data is param_const.
 * @tparam N the size/count of model paramters.
 */
template<std::size_t N>
class ParamsList : public BaseDataList<param_const, N> {
public:
    static size_t getParamsSize();
};

template<size_t N>
size_t ParamsList<N>::getParamsSize() {
    return N;
}

#endif //PNOHS_PARAMS_LIST_H
