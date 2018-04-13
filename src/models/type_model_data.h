//
// Created by wujiahao on 2018/4/6.
//

#ifndef PNOHS_TYPE_MODEL_DATA_H
#define PNOHS_TYPE_MODEL_DATA_H

#include <map>
#include <string>

class ModelDatas {

private:
    std::map<std::string,double> dDatas;
    std::map<std::string,int> iDatas;

public:
    void addData(std::string key, double value);
    void addData(std::string key, int value);

    template<typename T>
    T &at(const std::string &key);
};


#endif //PNOHS_TYPE_MODEL_DATA_H
