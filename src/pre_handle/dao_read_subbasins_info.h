//
// Created by wujiahao on 25/03/2018.
//

#ifndef PNOHS_DAO_READ_SUBBASINS_INFO_H
#define PNOHS_DAO_READ_SUBBASINS_INFO_H

#include <fstream>
#include <vector>
#include <map>
#include "constant.h"
#include "entity/info_subbasin.h"

class dao_read_subbasins_info {

public:

    void read_subbasin_allinfo_byid(const SUBBASIN_ID_TYPE subb_id, SUBBASIN_INFO_TYPE &out_subb_info);

    void read_subbasin_baseinfo_byid(const SUBBASIN_ID_TYPE subb_id, SUBBASIN_INFO_TYPE &out_subb_info);

    void read_subbasin_otherinfo_byid(const SUBBASIN_ID_TYPE subb_id, SUBBASIN_INFO_TYPE &out_subb_info);

    void read_subbasin_geoinfo_byid(const SUBBASIN_ID_TYPE subb_id, SUBBASIN_INFO_TYPE &out_subb_info);

    void read_subbasin_soilinfo_byid(const SUBBASIN_ID_TYPE subb_id, SUBBASIN_INFO_TYPE &out_subb_info);

    void read_subbasin_forceinfo_byid(const SUBBASIN_ID_TYPE subb_id, SUBBASIN_INFO_TYPE &out_subb_info);

    void
    read_subbasins_allinfo_byids(const SUBBASIN_ID_CONTAINER_TYPE subb_ids, SUBBASINS_CONTAINER_TYPE &out_subbs_info);

    void
    read_subbasins_baseinfo_byids(const SUBBASIN_ID_CONTAINER_TYPE subb_ids, SUBBASINS_CONTAINER_TYPE &out_subbs_info);

    void
    read_subbasins_otherinfo_byids(const SUBBASIN_ID_CONTAINER_TYPE subb_ids, SUBBASINS_CONTAINER_TYPE &out_subbs_info);

    void
    read_subbasins_geoinfo_byids(const SUBBASIN_ID_CONTAINER_TYPE subb_ids, SUBBASINS_CONTAINER_TYPE &out_subbs_info);

    void
    read_subbasins_soilinfo_byids(const SUBBASIN_ID_CONTAINER_TYPE subb_ids, SUBBASINS_CONTAINER_TYPE &out_subbs_info);

    void
    read_subbasins_forceinfo_byids(const SUBBASIN_ID_CONTAINER_TYPE subb_ids, SUBBASINS_CONTAINER_TYPE &out_subbs_inf);

    /**
     * 用于初始化，一次性读入本进程所要处理子流域的所有数据信息
     * 注意：调用该函数后，传入的out_subbs_info重新被初始化为包含所有子流域的所有描述数据，
     * 所以建议该函数只作为初始化使用(即传入的容器大小为0，而传出时为本进程所要处理的子流域总数)
     * 同时，由于该函数一次性读入本进程所要模拟的子流域数据，应考虑子流域多时的内存限制问题，此时可以考虑调用下面的all函数，每次只调用部分数据
     * @param out_subbs_info 保存本进程上的子流域信息的容器，（定义为map便于快速查找）
     */
    void read_subbasins_allinfo_all(SUBBASINS_CONTAINER_TYPE &out_subbs_info);

    /**
     * 用于初始化，一次性读入本进程所要处理子流域的基本数据信息(描述河网拓扑结构)
     * 注意：调用该函数后，传入的out_subbs_info重新被初始化为包含所有子流域的基本描述数据，
     * 所以建议该函数只作为初始化使用(即传入的容器大小为0，而传出时为本进程所要处理的子流域总数)
     * @param out_subbs_info 保存本进程上的子流域信息的容器，（定义为map便于快速查找）
     */
    void read_subbasins_baseinfo_all(SUBBASINS_CONTAINER_TYPE &out_subbs_info);

    /**
     * 用于初始化，一次性读入本进程所要处理子流域的除了描述河网拓扑的其他数据信息
     * 注意，该函数的传入容器的大小需要是本进程所要处理的子流域总数，同时该容器
     * @param out_subbs_info 保存本进程上的子流域信息的容器，（定义为map便于快速查找）
     */
    void read_subbasins_otherinfo_all(SUBBASINS_CONTAINER_TYPE &out_subbs_info);

    /**
     * 用于初始化，一次性读入本进程所要处理子流域的地理数据信息
     * @param out_subbs_info 保存本进程上的子流域信息的容器，（定义为map便于快速查找）
     */
    void read_subbasins_geoinfo_all(SUBBASINS_CONTAINER_TYPE &out_subbs_info);

    /**
     * 用于初始化，一次性读入本进程所要处理子流域的土壤数据信息
     * @param out_subbs_info 保存本进程上的子流域信息的容器，（定义为map便于快速查找）
     */
    void read_subbasins_soilinfo_all(SUBBASINS_CONTAINER_TYPE &out_subbs_info);

    /**
     * 用于初始化，一次性读入本进程所要处理子流域的大气数据信息
     * @param out_subbs_info 保存本进程上的子流域信息的容器，（定义为map便于快速查找）
     */
    void read_subbasins_forceinfo_all(SUBBASINS_CONTAINER_TYPE &out_subbs_inf);

    /**
     * 将this->fste当前读指针位置处开始的数据读入单个子流域数据中去
     * @param subb_info 输出参数，用于保存从文件中读出的子流域的全部数据
     */
    void read_one_subbasin_all_data(SUBBASIN_INFO_TYPE &subb_info);

    /**
     *
     * 将this->fste读指针移到位置offset处后，开始读入单个子流域数据中去
     * @param subb_info 输出参数，用于保存从文件中读出的子流域的全部数据
     * @param offset 该子流域全部数据在输入文件中的绝对偏移量
     */

    void read_one_subbasin_other_data(SUBBASIN_INFO_TYPE &subb_info);

    void read_one_subbasin_base_data(SUBBASIN_INFO_TYPE &subb_info);

    void read_one_subbasin_geo_data(SUBBASIN_INFO_TYPE &subb_info);

    void read_one_subbasin_soil_data(SUBBASIN_INFO_TYPE &subb_info);

    void read_one_subbasin_force_data(SUBBASIN_INFO_TYPE &subb_info);

//    void read_subb_info_gseek(OFFSET_TYPE offset);


    /**
     * 初始化读取指定输入文件中指定进程的工具类
     * @param filename  输入文件名
     * @param self_processor_id 进程ID
     */
    void init(const std::string &filename, const PROCESSOR_ID_TYPE self_processor_id);

    void finish();

    ~dao_read_subbasins_info();

    const SUBBASIN_ID_CONTAINER_TYPE &getSubbasin_ids() const;

    SUBBASIN_ID_TYPE getSubbasins_count() const;

private:

    /**
     * 读二进制输入文件中指定偏移量（offset，以字节byte为单位）出开始的数据到data中去
     * @param offset    所需读入数据在文件中的首偏移量
     * @param data      输出参数，存储读出的数据
     * @param size      输入参数，指定从offset读多少字节的数据
     * */
    void read_data_at_offset(const OFFSET_TYPE offset, char *data, size_t size);


    /**
     * 接着上次定位后的偏移出开始读，用于在连续文件空间中连续读取多次
     * @param data      输出参数，存储读出的数据
     * @param size      输入参数，指定从offset读多少字节的数据
     */
    void read_data_continuous(char *data, size_t size);

    /**
     *获取自己所要模拟的子流域个数this->subbasins_count
     */
    void read_subbasins_count();

    /**
     * 获取自己所要模拟的各个子流域的id this->subbasin_ids;
     */
    void read_subbasin_ids();

    /**
     * 获取自己所要模拟的各个子流域在输入文件中的偏移量this->subbsins_info_offsets;
     */
    void read_subbasins_info_offsets();

    /**
     * 根据子流域id，得到它在输入文件中的绝对偏移量
     * @param subb_id  子流域ID号
     * @return 该子流域在输入文件中的绝对偏移量
     */
    OFFSET_TYPE get_offset_by_id(SUBBASIN_ID_TYPE subb_id);

    /**
     * 计算实例的基本数据所占内存空间大小
     * @return  子流域实例的基本数据所占内存空间大小
     */
    OFFSET_TYPE solve_base_data_size(SUBBASIN_INFO_TYPE &subb_info);

    OFFSET_TYPE start_offset;           //本进程所要模拟的子流域数据在输入文件中的绝对首偏移量
    OFFSET_TYPE first_subbasin_offset;  //本进程所要模拟的第一个子流域的实际数据在输入文件中偏移量
    std::fstream fs;                   //输入文件的输入流
    SUBBASIN_ID_TYPE subbasins_count;

    //本进程所要模拟的子流域数目
    OFFSETS_CONTAINER_TYPE subbasins_info_offsets; //本进程所要模拟各个子流域数据在输入文件中相对于first_subbasin_offset的相对偏移量
    SUBBASIN_ID_CONTAINER_TYPE subbasin_ids;           //本进程所要模拟的各个子流域的id
};


#endif //PNOHS_DAO_READ_SUBBASINS_INFO_H
