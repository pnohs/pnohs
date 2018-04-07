//
// Created by wujiahao on 2018/4/6.
//

#include <iostream>
#include "type_model_data.h"


void ModelDatas::addData(std::string key, double value) {
    this->dDatas["key"] = value;
}

void ModelDatas::addData(std::string key, int value) {
    this->iDatas["key"] = value;
}

template<typename T>
T &ModelDatas::at(const std::string &key) {
    if (typeid(T).name() == typeid(double).name())
        return this->dDatas[key];
    if (typeid(T).name() == typeid(int).name())
        return this->iDatas[key];

    std::cerr << "err type of T" << std::endl;
    exit(-1);
}
