//
// Created by wujiahao on 24/03/2018.
//

#ifndef PNOHS_CONSTANT_H
#define PNOHS_CONSTANT_H

#include "entity/info_subbasin.h"
#include <vector>
#include <string>
#include <iostream>

//Custom types used in reading subbasion info for improving maintainability
#define OFFSET_TYPE                                 unsigned long  //define offset'type
#define SUBBASIN_INFO_TYPE                          info_subbasin
#define SUBBASINS_CONTAINER_TYPE                    std::map<SUBBASIN_ID_TYPE,SUBBASIN_INFO_TYPE *> //define map for storing subbasins and searching fast by subbsin_id
#define OFFSETS_CONTAINER_TYPE                      std::vector<OFFSET_TYPE>


#define FIRST_UNUSELESS_OFFSET                      sizeof(OFFSET_TYPE)


enum{
    TAG_ALL_INFO,                           //代表读入用于该子流域的全部数据、
    TAG_BASE_INFO,                          //代表只读入与河网拓扑有关的基本数据
    TAG_OTHER_INFO,                         //代表读入除TAG_BASE_INFO以外的子流域数据
    TAG_GEO_INFO,                           //代表读入地理相关的数据
    TAG_SOIL_INFO,                          //代表读入土壤相关数据
    TAG_FORCE_INFO                          //代表读入大气相关数据
};


class err_handle{
public:
    static void sys_err(std::string msg, int merrno){
        std::cerr << msg << std::endl;
        exit(merrno);
    }
};

#endif //PNOHS_CONSTANT_H
