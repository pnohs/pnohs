//
// Created by genshen on 8/12/18.
//

#ifndef PNOHS_BASE_DATA_LIST_H
#define PNOHS_BASE_DATA_LIST_H

#include <array>
#include "model_params_def.h"

/**
 * data structure for storing model data, including model parameters, model status-variables.
 * @tparam T the type of data.
 * @tparam N the count/size of data, which is the size of {std::array data}.
 */
template<typename T, std::size_t N>
class BaseDataList {
public:
    /*
     * all data are saved here.
     */
    std::array<T, N> data;

    /**
     * copy data from src to data.
     * The src type is std::array.
     * @param src
     */
    void setValues(std::array<T, N> &src);

    /**
     * copy data from src to data.
     * the src type is c style array.
     * the data copy will copy min{@param n,@def N} counts of elements to data.
     * @param src the pointer to c style array.
     * @param n the size of c style array.
     */
    void setValues(T *src, std::size_t n);
};

template<typename T, size_t N>
void BaseDataList<T, N>::setValues(std::array<T, N> &src) {
    data = src;
}

template<typename T, size_t N>
void BaseDataList<T, N>::setValues(T *src, std::size_t n) {
    std::size_t ele_n = n < N ? n : N;
    std::copy(src, src + ele_n, std::begin(data));
}

#endif //PNOHS_BASE_DATA_LIST_H
