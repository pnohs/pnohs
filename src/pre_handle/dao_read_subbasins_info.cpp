//
// Created by wujiahao on 25/03/2018.
//

#include <iostream>
#include "dao_read_subbasins_info.h"
#include "entity/info_subbasin.h"

void dao_read_subbasins_info::read_data_at_offset(const OFFSET_TYPE offset, char *data, size_t size) {
    this->fste.seekg(offset);
    this->fste.read(data, size);
}

void dao_read_subbasins_info::read_data_continuous(char *data, size_t size) {
    this->fste.read(data, size);
}


void dao_read_subbasins_info::read_subbasins_count() {
    this->read_data_at_offset(this->start_offset,
                              reinterpret_cast<char *>(&this->subbasins_count),
                              sizeof(this->subbasins_count));
    if (this->subbasins_count <= 0) {
        err_handle::sys_err("subbasins_count can't be 0", -1);
    }
}

void dao_read_subbasins_info::read_subbasins_info_offsets() {

    //使用C++11特性,data()函数
    this->subbasins_info_offsets.resize(this->subbasins_count);
    this->read_data_at_offset(this->start_offset + sizeof(SUBBASIN_ID_TYPE),
                              reinterpret_cast<char *>(this->subbasins_info_offsets.data()),
                              this->subbasins_count * sizeof(OFFSET_TYPE));
}

void dao_read_subbasins_info::read_subbasin_ids() {

    SUBBASIN_ID_TYPE tmp_id;
    for (int i = 0; i < this->subbasins_count; i++) {
        this->read_data_at_offset(this->first_subbasin_offset + this->subbasins_info_offsets[i],
                                  reinterpret_cast<char *>(&tmp_id), sizeof(SUBBASIN_ID_TYPE));
        this->subbasin_ids.push_back(tmp_id);
    }

}

void dao_read_subbasins_info::init(const std::string &filename, const PROCESSOR_ID_TYPE self_processor_id) {

    //打开二进制输入文件
    this->fste.open(filename, OPEN_READ_BINARY_FILE_MODE);

    if (!fste) {
        //出错处理需要额外的模板，暂时先这样
        err_handle::sys_err("file" + filename + "not exit", -1);
    }
    //读取本进程所需子流域数据在输入文件中的最开始偏移量this->start_offset
    this->read_data_at_offset(FIRST_UNUSELESS_OFFSET + self_processor_id * sizeof(OFFSET_TYPE),
                              reinterpret_cast<char *>(&this->start_offset),
                              sizeof(this->start_offset));
    //读取本进程需要模拟的总子流域数目
    this->read_subbasins_count();

    //计算本进程第一个子流域信息在输入文件中的偏移位置
    // （此等式代表：输入文件中子流域偏移量数据即this->subbasins_info_offsets中的偏移量是相对于第一个子流域数据的相对偏移量）
    this->first_subbasin_offset = this->start_offset + sizeof(SUBBASIN_ID_TYPE) +
                                  this->subbasins_count * sizeof(OFFSET_TYPE);

    //读取各子流域信息在输入文件中的相对偏移量
    this->read_subbasins_info_offsets();

    //读取本进程需要模拟的各个子流域ID
    this->read_subbasin_ids();

}

void dao_read_subbasins_info::finish() {
    this->fste.close();
}

dao_read_subbasins_info::~dao_read_subbasins_info() {
    this->finish();
}

void dao_read_subbasins_info::read_subbasin_allinfo_byid(const SUBBASIN_ID_TYPE subb_id,
                                                         SUBBASIN_INFO_TYPE &out_subb_info) {

    // 1.根据子流域id计算子流域数据在输入文件中的绝对偏移量
    OFFSET_TYPE subb_offset = this->get_offset_by_id(subb_id);
    this->fste.seekg(subb_offset);

    // 2.读入数据到out_subb_info
    this->read_one_subbasin_all_data(out_subb_info);
}

void dao_read_subbasins_info::read_subbasin_baseinfo_byid(const SUBBASIN_ID_TYPE subb_id,
                                                          SUBBASIN_INFO_TYPE &out_subb_info) {

    // 1.根据子流域id计算子流域数据在输入文件中的绝对偏移量
    OFFSET_TYPE subb_offset = this->get_offset_by_id(subb_id);
    this->fste.seekg(subb_offset);

    // 2.读入基本数据到out_subb_info
    this->read_one_subbasin_base_data(out_subb_info);
}

void dao_read_subbasins_info::read_subbasin_otherinfo_byid(const SUBBASIN_ID_TYPE subb_id,
                                                           SUBBASIN_INFO_TYPE &out_subb_info) {
    // 1.根据子流域id计算子流域其他类型数据在输入文件中的绝对偏移量
    OFFSET_TYPE subb_offset = this->get_offset_by_id(subb_id) + this->solve_base_data_size(out_subb_info);
    this->fste.seekg(subb_offset);

    // 2.读入other数据到out_subb_info
    this->read_one_subbasin_other_data(out_subb_info);

}

void dao_read_subbasins_info::read_subbasin_geoinfo_byid(const SUBBASIN_ID_TYPE subb_id,
                                                         SUBBASIN_INFO_TYPE &out_subb_info) {

    // 1.根据子流域id计算子流域geo数据在输入文件中的绝对偏移量
    OFFSET_TYPE subb_offset = this->get_offset_by_id(subb_id)
                              + this->solve_base_data_size(out_subb_info);
    this->fste.seekg(subb_offset);

    // 2.读入geo数据到out_subb_info
    this->read_one_subbasin_geo_data(out_subb_info);
}

void dao_read_subbasins_info::read_subbasin_soilinfo_byid(const SUBBASIN_ID_TYPE subb_id,
                                                          SUBBASIN_INFO_TYPE &out_subb_info) {
    // 1.根据子流域id计算子流域soil数据在输入文件中的绝对偏移量
    OFFSET_TYPE subb_offset = this->get_offset_by_id(subb_id)
                              + this->solve_base_data_size(out_subb_info)
                              + sizeof(*out_subb_info.getGeo_data());

    this->fste.seekg(subb_offset);

    // 2.读入soil数据到out_subb_info
    this->read_one_subbasin_soil_data(out_subb_info);

}

void dao_read_subbasins_info::read_subbasin_forceinfo_byid(const SUBBASIN_ID_TYPE subb_id,
                                                           SUBBASIN_INFO_TYPE &out_subb_info) {

    // 1.根据子流域id计算子流域force数据在输入文件中的绝对偏移量
    OFFSET_TYPE subb_offset = this->get_offset_by_id(subb_id)
                              + this->solve_base_data_size(out_subb_info)
                              + sizeof(*out_subb_info.getGeo_data()) + sizeof(*out_subb_info.getSoil_data());

    this->fste.seekg(subb_offset);

    // 2.读入基本数据到out_subb_info
    this->read_one_subbasin_force_data(out_subb_info);
}

const SUBBASIN_ID_CONTAINER_TYPE &dao_read_subbasins_info::getSubbasin_ids() const {
    return this->subbasin_ids;
}

void dao_read_subbasins_info::read_subbasins_allinfo_byids(const SUBBASIN_ID_CONTAINER_TYPE subb_ids,
                                                           SUBBASINS_CONTAINER_TYPE &out_subbs_info) {

}

void dao_read_subbasins_info::read_subbasins_baseinfo_byids(const SUBBASIN_ID_CONTAINER_TYPE subb_ids,
                                                            SUBBASINS_CONTAINER_TYPE &out_subbs_info) {

}

void dao_read_subbasins_info::read_subbasins_geoinfo_byids(const SUBBASIN_ID_CONTAINER_TYPE subb_ids,
                                                           SUBBASINS_CONTAINER_TYPE &out_subbs_info) {

}

void dao_read_subbasins_info::read_subbasins_soilinfo_byids(const SUBBASIN_ID_CONTAINER_TYPE subb_ids,
                                                            SUBBASINS_CONTAINER_TYPE &out_subbs_info) {

}

void dao_read_subbasins_info::read_subbasins_forceinfo_byids(const SUBBASIN_ID_CONTAINER_TYPE subb_ids,
                                                             SUBBASINS_CONTAINER_TYPE &out_subbs_inf) {

}

void dao_read_subbasins_info::read_subbasins_allinfo_all(SUBBASINS_CONTAINER_TYPE &out_subbs_info) {

    SUBBASIN_INFO_TYPE *subb_info = nullptr;
    //1.读指针跳转到本进程第一个子流域有效数据的首部
    this->fste.seekg(this->first_subbasin_offset);

    // 2.读数据
    for (int i = 0; i < this->subbasins_count; i++) {
        subb_info = new SUBBASIN_INFO_TYPE;
        this->read_one_subbasin_all_data(*subb_info);
        //out_subbs_info[subb_info->getSubbasin_id()] = subb_info; // 存在效率问题，因为是第一次插入，使用改种方式会先检查容器中是否存在该子流域ID
        out_subbs_info.insert(SUBBASINS_CONTAINER_TYPE::value_type(subb_info->getSubbasin_id(), subb_info));
    }
}

void dao_read_subbasins_info::read_subbasins_baseinfo_all(SUBBASINS_CONTAINER_TYPE &out_subbs_info) {
    SUBBASIN_INFO_TYPE *subb_info = nullptr;
    SUBBASIN_ID_TYPE tmp;
    for (int i = 0; i < this->subbasins_count; i++) {
        subb_info = new SUBBASIN_INFO_TYPE;

        this->fste.seekg(this->first_subbasin_offset + this->subbasins_info_offsets[i]);
        this->read_one_subbasin_base_data(*subb_info);

        //out_subbs_info[subb_info->getSubbasin_id()] = subb_info; // 存在效率问题，因为是第一次插入，使用改种方式会先检查容器中是否存在该子流域ID
        out_subbs_info.insert(SUBBASINS_CONTAINER_TYPE::value_type(subb_info->getSubbasin_id(), subb_info));
    }
}

void dao_read_subbasins_info::read_subbasins_geoinfo_all(SUBBASINS_CONTAINER_TYPE &out_subbs_info) {

    OFFSET_TYPE subb_offset;
    // 遍历out_subbs_info
    SUBBASINS_CONTAINER_TYPE::iterator it = out_subbs_info.begin();
    for (; it != out_subbs_info.end(); it++) {

        // 1.根据子流域id计算每个子流域数据在输入文件中的绝对偏移量
        subb_offset = this->get_offset_by_id(it->first);
        // 2.计算单个子流域其他类型数据在输入文件中的绝对偏移量
        subb_offset += this->solve_base_data_size(*it->second);
        this->fste.seekg(subb_offset);
        // 3.开始读取数据
        this->read_one_subbasin_geo_data(*it->second);
    }
}

void dao_read_subbasins_info::read_subbasins_soilinfo_all(SUBBASINS_CONTAINER_TYPE &out_subbs_info) {
    OFFSET_TYPE subb_offset;
    // 遍历out_subbs_info
    SUBBASINS_CONTAINER_TYPE::iterator it = out_subbs_info.begin();
    for (; it != out_subbs_info.end(); it++) {

        // 1.根据子流域id计算每个子流域数据在输入文件中的绝对偏移量
        subb_offset = this->get_offset_by_id(it->first);
        // 2.计算单个子流域其他类型数据在输入文件中的绝对偏移量
        subb_offset += this->solve_base_data_size(*it->second) + sizeof(*it->second->getGeo_data());
        this->fste.seekg(subb_offset);
        // 3.开始读取数据
        this->read_one_subbasin_soil_data(*it->second);
    }
}

void dao_read_subbasins_info::read_subbasins_forceinfo_all(SUBBASINS_CONTAINER_TYPE &out_subbs_info) {
    OFFSET_TYPE subb_offset;
    // 遍历out_subbs_info
    SUBBASINS_CONTAINER_TYPE::iterator it = out_subbs_info.begin();
    for (; it != out_subbs_info.end(); it++) {

        // 1.根据子流域id计算每个子流域数据在输入文件中的绝对偏移量
        subb_offset = this->get_offset_by_id(it->first);

        // 2.计算单个子流域其他类型数据在输入文件中的绝对偏移量
        subb_offset += this->solve_base_data_size(*it->second)
                       + sizeof(*it->second->getGeo_data())
                       + sizeof(*it->second->getSoil_data());

        this->fste.seekg(subb_offset);
        // 3.开始读取数据
        this->read_one_subbasin_force_data(*it->second);
    }
}

void dao_read_subbasins_info::read_subbasins_otherinfo_all(SUBBASINS_CONTAINER_TYPE &out_subbs_info) {

    OFFSET_TYPE subb_offset;
    // 遍历out_subbs_info
    SUBBASINS_CONTAINER_TYPE::iterator it = out_subbs_info.begin();
    for (; it != out_subbs_info.end(); it++) {

        // 1.根据子流域id计算每个子流域数据在输入文件中的绝对偏移量
        subb_offset = this->get_offset_by_id(it->first);
        // 2.计算单个子流域其他类型数据在输入文件中的绝对偏移量
        subb_offset += this->solve_base_data_size(*it->second);
        this->fste.seekg(subb_offset);
        // 3.开始读取数据
        this->read_one_subbasin_other_data(*it->second);
    }

}

void dao_read_subbasins_info::read_subbasins_otherinfo_byids(const SUBBASIN_ID_CONTAINER_TYPE subb_ids,
                                                             SUBBASINS_CONTAINER_TYPE &out_subbs_info) {
}

SUBBASIN_ID_TYPE dao_read_subbasins_info::getSubbasins_count() const {
    return this->subbasins_count;
}

OFFSET_TYPE dao_read_subbasins_info::get_offset_by_id(SUBBASIN_ID_TYPE subb_id) {
    int index;
    OFFSET_TYPE offset = 0;
    for (index = 0; index < this->subbasins_count; index++) {
        if (this->subbasin_ids[index] == subb_id)
            break;
    }
    offset = this->first_subbasin_offset + this->subbasins_info_offsets[index];
    return offset;
}

void dao_read_subbasins_info::read_one_subbasin_other_data(SUBBASIN_INFO_TYPE &subb_info) {
    this->read_one_subbasin_geo_data(subb_info);
    this->read_one_subbasin_soil_data(subb_info);
    this->read_one_subbasin_force_data(subb_info);
}

//void dao_read_subbasins_info::read_subb_info_gseek(OFFSET_TYPE offset) {
//    this->fste.seekg(offset);
//}

void dao_read_subbasins_info::read_one_subbasin_all_data(SUBBASIN_INFO_TYPE &subb_info) {
    this->read_one_subbasin_base_data(subb_info);
    this->read_one_subbasin_other_data(subb_info);
}

void dao_read_subbasins_info::read_one_subbasin_base_data(SUBBASIN_INFO_TYPE &subb_info) {

    SUBBASIN_ID_TYPE tmp_id;
    SUBBASIN_COUNT_TYPE tmp_count;
    this->fste.read(reinterpret_cast<char *>(&tmp_id), sizeof(SUBBASIN_ID_TYPE));
    subb_info.setSubbasin_id(tmp_id);
    this->fste.read(reinterpret_cast<char *>(&tmp_count), sizeof(SUBBASIN_COUNT_TYPE));
    subb_info.setDown_subbasin_count(tmp_count);
    this->fste.read(reinterpret_cast<char *>(&tmp_count), sizeof(SUBBASIN_COUNT_TYPE));
    subb_info.setUp_subbasin_count(tmp_count);


    if (!subb_info.getDown_subbasin_ids()) {
        subb_info.setDown_subbasin_ids(new SUBBASIN_ID_CONTAINER_TYPE(subb_info.getDown_subbasin_count()));
    } else {
        subb_info.getDown_subbasin_ids()->resize(subb_info.getDown_subbasin_count());
    }
    this->fste.read(reinterpret_cast<char *>(subb_info.getDown_subbasin_ids()->data()),
                    sizeof(SUBBASIN_ID_TYPE) * subb_info.getDown_subbasin_count());
    if (!subb_info.getDown_subbasin_belong_processor()) {
        subb_info.setDown_subbasin_belong_processor(
                new PROCESSOR_ID_CONTAINER_TYPE(subb_info.getDown_subbasin_count()));
    } else {
        subb_info.getDown_subbasin_belong_processor()->resize(subb_info.getDown_subbasin_count());
    }
    this->fste.read(reinterpret_cast<char *>(subb_info.getDown_subbasin_belong_processor()->data()),
                    sizeof(PROCESSOR_ID_TYPE) * subb_info.getDown_subbasin_count());


    if (!subb_info.getUp_subbasin_ids()) {
        subb_info.setUp_subbasin_ids(new SUBBASIN_ID_CONTAINER_TYPE(subb_info.getUp_subbasin_count()));
    } else {
        subb_info.getUp_subbasin_ids()->resize(subb_info.getUp_subbasin_count());
    }
    this->fste.read(reinterpret_cast<char *>(subb_info.getUp_subbasin_ids()->data()),
                    sizeof(SUBBASIN_ID_TYPE) * subb_info.getUp_subbasin_count());
    if (!subb_info.getUp_subbasin_belong_processor()) {
        subb_info.setUp_subbasin_belong_processor(new PROCESSOR_ID_CONTAINER_TYPE(subb_info.getUp_subbasin_count()));
    } else {
        subb_info.getUp_subbasin_belong_processor()->resize(subb_info.getUp_subbasin_count());
    }
    this->fste.read(reinterpret_cast<char *>(subb_info.getUp_subbasin_belong_processor()->data()),
                    sizeof(PROCESSOR_ID_TYPE) * subb_info.getUp_subbasin_count());

}

void dao_read_subbasins_info::read_one_subbasin_soil_data(SUBBASIN_INFO_TYPE &subb_info) {
    if (!subb_info.getSoil_data())
        subb_info.setSoil_data(new soil_info_subbasin);
    this->fste.read(reinterpret_cast<char *>(subb_info.getSoil_data()), sizeof(*subb_info.getSoil_data()));
}

void dao_read_subbasins_info::read_one_subbasin_force_data(SUBBASIN_INFO_TYPE &subb_info) {
    if (!subb_info.getForce_data())
        subb_info.setForce_data(new force_info_subbasin);
    this->fste.read(reinterpret_cast<char *>(subb_info.getForce_data()), sizeof(*subb_info.getForce_data()));
}

void dao_read_subbasins_info::read_one_subbasin_geo_data(SUBBASIN_INFO_TYPE &subb_info) {
    if (!subb_info.getGeo_data()) {
        subb_info.setGeo_data(new geo_info_subbasin);
    }
    this->fste.read(reinterpret_cast<char *>(subb_info.getGeo_data()), sizeof(*subb_info.getGeo_data()));
}

OFFSET_TYPE dao_read_subbasins_info::solve_base_data_size(SUBBASIN_INFO_TYPE &subb_info) {
    return sizeof(SUBBASIN_ID_TYPE) + sizeof(SUBBASIN_COUNT_TYPE) * 2
           + (subb_info.getDown_subbasin_count() + subb_info.getUp_subbasin_count())
             * (sizeof(SUBBASIN_ID_TYPE) + sizeof(PROCESSOR_ID_TYPE));
}
