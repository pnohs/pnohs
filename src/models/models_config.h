//
// Created by wujiahao on 2018/4/6.
//

#ifndef PNOHS_MODEL_CONFIG_H
#define PNOHS_MODEL_CONFIG_H

#include <string>
#include <map>
#include <vector>

namespace mlcg {

    // 定义各模型参数的存储容器类型以及需要的输入数据的类型
    typedef  std::map<std::string,double> _type_dparas;
    typedef  std::map<std::string,int> _type_iparas;

    typedef  std::map<std::string,double[2]> _type_dpara_thresholds;
    typedef  std::map<std::string,int[2]> _type_ipara_thresholds;

    typedef  std::map<std::string,double> _type_ddatas;
    typedef  std::map<std::string,int> _type_idatas;

    typedef std::vector<std::string> _type_data_names;

    // 定义各个模型需要的参数的名称
    static const std::string _pname_rate_parameter = "cevp";
    static const std::string _pname_air_temperature_threshold = "ttmp";
    static const std::string _pname_seasonal_factor = "cseason";

    //定义各个模型需要的输入数据的名称
    static const std::string _dname_air_temperature = "temp";


}
#endif //PNOHS_MODEL_CONFIG_H
