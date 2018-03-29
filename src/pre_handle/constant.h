//
// Created by wujiahao on 24/03/2018.
//

#include <iostream>
#include <vector>
#include <map>

#ifndef PNOHS_CONSTANT_H
#define PNOHS_CONSTANT_H


//Custom types used in reading subbasion info for improving maintainability

#ifndef SUBBASIN_ID_TYPE
#define SUBBASIN_ID_TYPE                            unsigned long
#endif

#ifndef SUBBASIN_COUNT_TYPE
#define SUBBASIN_COUNT_TYPE                         unsigned long
#endif
#ifndef SUBBASIN_ID_CONTAINER_TYPE
#define SUBBASIN_ID_CONTAINER_TYPE                  std::vector<SUBBASIN_ID_TYPE>
#endif

#ifndef OFFSET_TYPE
#define OFFSET_TYPE                                 unsigned long  //define offset'type
#endif
#ifndef OFFSETS_CONTAINER_TYPE
#define OFFSETS_CONTAINER_TYPE                      std::vector<OFFSET_TYPE>
#endif

#ifndef SUBBASIN_INFO_TYPE
#define SUBBASIN_INFO_TYPE                          info_subbasin
#endif

#ifndef SUBBASINS_CONTAINER_TYPE
#define SUBBASINS_CONTAINER_TYPE                    std::map<SUBBASIN_ID_TYPE,SUBBASIN_INFO_TYPE *> //define map for storing subbasins and searching fast by subbsin_id
#endif

#ifndef PROCESSOR_ID_TYPE
#define PROCESSOR_ID_TYPE                           unsigned long //define process id 's type
#endif
#ifndef PROCESSOR_ID_CONTAINER_TYPE
#define PROCESSOR_ID_CONTAINER_TYPE                 std::vector<PROCESSOR_ID_TYPE>
#endif

#ifndef FIRST_UNUSELESS_OFFSET
#define FIRST_UNUSELESS_OFFSET                      sizeof(OFFSET_TYPE)
#endif

// 打开输入的二进制文件进行读取的模式
#ifndef OPEN_READ_BINARY_FILE_MODE
#define OPEN_READ_BINARY_FILE_MODE                  (std::ios::in | std::ios::binary)
#endif
//打开输出的二进制文件进行写数据的模式
#ifndef OPEN_WRITE_BINARY_FILE_MODE
#define OPEN_WRITE_BINARY_FILE_MODE                 (std::ios::binary | std::ios::trunc | std::ios::out)
#endif

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
