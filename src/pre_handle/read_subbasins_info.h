//
// Created by wujiahao on 24/03/2018.
//

#ifndef PNOHS_READ_SUBBASINS_INFO_H
#define PNOHS_READ_SUBBASINS_INFO_H

#include <string>
#include <fstream>
#include "constant.h"
#include "dao_read_subbasins_info.h"

class read_subbasins_info {

public:
    /**
     * 初始化此类时需要传递输入文件的文件名以及本进程的进程号
     * @param filename 输入文件
     * @param self_processor_id 本进程id
     */
    read_subbasins_info(const std::string &filename, const PROCESSOR_ID_TYPE self_processor_id);

    /**
     * 根据子流域id，和tag，选择性地从文件中读入单个子流域的某部分数据:
     * 考虑到神威内存容量小而子流域描述数据又很多，可能无法一次性将本进程模拟的所有子流域信息都读入，则需要用时读取
     * @param subbasin_id 子流域ID
     * @param subb_info 子流域数据存储容器
     * @param tag 标识次调用将读入哪部分数据：      TAG_ALL_INFO代表读入用于该子流域的全部数据、
     *                                          TAG_BASE_INFO代表只读入与河网拓扑有关的基本数据
     *                                          TAG_OTHER_INFO代表读入除TAG_BASE_INFO以外的子流域数据
     *                                          TAG_GEO_INFO代表读入地理相关的数据
     *                                          TAG_SOIL_INFO代表读入土壤相关数据
     *                                          TAG_FORCE_INFO代表读入大气相关数据
     */
    void add_one_subasin(const SUBBASIN_ID_TYPE subbasin_id, SUBBASIN_INFO_TYPE &subb_info, int tag);

    /**
     * 根据多个子流域id，和tag，选择性地从文件中读入该些个子流域的某部分数据:
     * 考虑到神威内存容量小而子流域描述数据又很多，可能无法一次性将本进程模拟的所有子流域信息都读入，则需要用时读取
     * @param subbasin_id 子流域ID
     * @param subbasins 本进程已读入子流域数据存储容器
     * @param tag 标识次调用将读入哪部分数据：      TAG_ALL_INFO代表读入用于该子流域的全部数据、
     *                                          TAG_BASE_INFO代表只读入与河网拓扑有关的基本数据
     *                                          TAG_OTHER_INFO代表读入除TAG_BASE_INFO以外的子流域数据
     *                                          TAG_GEO_INFO代表读入地理相关的数据
     *                                          TAG_SOIL_INFO代表读入土壤相关数据
     *                                          TAG_FORCE_INFO代表读入大气相关数据
     */
    void add_some_subasins(const SUBBASIN_ID_CONTAINER_TYPE &subbasin_ids, SUBBASINS_CONTAINER_TYPE &subbasins, int tag);

    /**
     * 根据tag，选择性地从文件中读入本进程所需要模拟子流域的某部分数据:
     * 考虑到神威内存容量小而子流域描述数据又很多，可能无法一次性将本进程模拟的所有子流域信息都读入，则需要用时读取
     * @param subbasin_id 子流域ID
     * @param subbasins 本进程已读入子流域数据存储容器
     * @param tag 标识次调用将读入哪部分数据：      TAG_ALL_INFO代表读入用于该子流域的全部数据、
     *                                          TAG_BASE_INFO代表只读入与河网拓扑有关的基本数据
     *                                          TAG_OTHER_INFO代表读入除TAG_BASE_INFO以外的子流域数据
     *                                          TAG_GEO_INFO代表读入地理相关的数据
     *                                          TAG_SOIL_INFO代表读入土壤相关数据
     *                                          TAG_FORCE_INFO代表读入大气相关数据
     */
    void add_all_subbasins(SUBBASINS_CONTAINER_TYPE &subbasins, int tag);

    /**
     * 在流域数据容器中移除指定id的流域
     * @param subbasin_id
     * @param subbasins
     */
    void remove_one_subasin(const SUBBASIN_ID_TYPE subbasin_id, SUBBASINS_CONTAINER_TYPE &subbasins);

    /**
     * 在流域数据容器中移除多个子流域数据
     * @param subbasin_id
     * @param subbasins
     */
    void remove_some_subasins(const SUBBASIN_ID_CONTAINER_TYPE subbasin_ids, SUBBASINS_CONTAINER_TYPE &subbasins);

    /**
     *清除子流域数据容器中所有子流域数据
     * @param subbasins
     */
    void remove_all_subbasins(SUBBASINS_CONTAINER_TYPE &subbasins);


    /**
     * 获取本进程需要处理的各个子流域的id,用于内存有限时，读入指定id的子流域数据
     * @return
     */
    const SUBBASIN_ID_CONTAINER_TYPE &read_subbasin_all_ids();

    /**
     * 获得本进程需要处理的子流域总数
     * @return
     */
    SUBBASIN_ID_TYPE get_subbasins_count();

private:

    void finish();

    dao_read_subbasins_info dao_rsi;
};

#endif //PNOHS_READ_SUBBASINS_INFO_H
