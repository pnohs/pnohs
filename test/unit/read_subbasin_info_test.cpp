//
// Created by wujiahao on 26/03/2018.
//

#ifndef PNOHS_TEST_READ_SUBBASIN_INFO_H
#define PNOHS_TEST_READ_SUBBASIN_INFO_H

#include <gtest/gtest.h>
#include <fstream>
#include <utils/mpi_utils.h>
#include "pre_handle/read_subbasins_info.h"

/**
 * 该方法生成测试用的子流域数据
 */
static void format_input_file() {
    PROCESSOR_ID_TYPE processor_count = 10; //kiwi::mpiUtils::allRanks;
    std::vector<SUBBASIN_ID_TYPE> subbs_count_at_one_processor;
    std::vector<std::vector<info_subbasin *> *> datas;
    std::vector<std::vector<OFFSET_TYPE> *> subb_offsets_at_diff_proc;
    std::vector<OFFSET_TYPE> all_subb_size_on_diff_proc;
    all_subb_size_on_diff_proc.resize(processor_count, 0);

    for (int i = 0; i < processor_count; i++) {
        std::vector<info_subbasin *> *tmp_data = new std::vector<info_subbasin *>;
        std::vector<OFFSET_TYPE> *tmp_subb_offsets = new std::vector<OFFSET_TYPE>;
        subbs_count_at_one_processor.push_back(i + 1);
        tmp_subb_offsets->resize(subbs_count_at_one_processor[i]);

        OFFSET_TYPE pre_subb_data_size = 0;
        for (int j = 0; j < subbs_count_at_one_processor[i]; j++) {
            info_subbasin *tmp_subb = new info_subbasin(j + 3, j + i + 1, j * (i + 1));

            for (int k = 0; k < tmp_subb->down_subbasin_count; k++) {
                tmp_subb->down_subbasin_ids->push_back(k + j);
                tmp_subb->down_subbasin_belong_processor->push_back(i + k);
            }

            for (int k = 0; k < tmp_subb->up_subbasin_count; k++) {
                tmp_subb->up_subbasin_ids->push_back(k + i);
                tmp_subb->up_subbasin_belong_processor->push_back(i + k);
            }

            tmp_subb->setGeo_data(new geo_info_subbasin());
            tmp_subb->geo_data->elev = 200.8 + j + i;
            tmp_subb->geo_data->lat = 127.8 + i + j;
            tmp_subb->geo_data->lon = 80.8 + i + j;

            tmp_subb->setForce_data(new force_info_subbasin);
            tmp_subb->force_data->air_tmp = 24.8 + i + j;

            tmp_subb->setSoil_data(new soil_info_subbasin);
            tmp_subb->soil_data->soil_layers = 10; // todo set data

            tmp_data->push_back(tmp_subb);

            if (j == 0) {
                tmp_subb_offsets->at(j) = pre_subb_data_size;
            } else {
                tmp_subb_offsets->at(j) = pre_subb_data_size + tmp_subb_offsets->at(j - 1);
            }

            pre_subb_data_size = sizeof(tmp_subb->subbasin_id)
                                 + sizeof(tmp_subb->up_subbasin_count)
                                 + sizeof(tmp_subb->down_subbasin_count)
                                 + sizeof(SUBBASIN_ID_TYPE) * tmp_subb->down_subbasin_count +
                                 sizeof(PROCESSOR_ID_TYPE) * tmp_subb->down_subbasin_count
                                 + sizeof(SUBBASIN_ID_TYPE) * tmp_subb->up_subbasin_count +
                                 sizeof(PROCESSOR_ID_TYPE) * tmp_subb->up_subbasin_count
                                 //+ sizeof(tmp_subb->geo_data->lon) + sizeof(tmp_subb->geo_data->lat) + sizeof(tmp_subb->geo_data->elev)
                                 + sizeof(*tmp_subb->geo_data)
                                 //+ sizeof(tmp_subb->soil_data->soil_layers)
                                 + sizeof(*tmp_subb->soil_data)
                                 //+ sizeof(tmp_subb->force_data->air_tmp);
                                 + sizeof(*tmp_subb->force_data);

            all_subb_size_on_diff_proc[i] += pre_subb_data_size;
        }
        datas.push_back(tmp_data);
        subb_offsets_at_diff_proc.push_back(tmp_subb_offsets);
    }

    //2.写入输入文件input.bin中去
    std::fstream fp("input.bin", std::ios::binary | std::ios::trunc | std::ios::out);
    //2.1计算各进程数据的初始偏移量
    std::vector<OFFSET_TYPE> firse_offsets;
    firse_offsets.resize(processor_count);
    firse_offsets[0] = sizeof(PROCESSOR_ID_TYPE) + processor_count * sizeof(OFFSET_TYPE);
    for (int i = 1; i < processor_count; i++) {
        firse_offsets[i] = firse_offsets[i - 1] + all_subb_size_on_diff_proc[i - 1]
                           + sizeof(SUBBASIN_ID_TYPE)
                           + subbs_count_at_one_processor[i - 1] * sizeof(OFFSET_TYPE);
    }
    //2.2写计算单元数
    fp.write(reinterpret_cast<const char *>(&processor_count), sizeof(processor_count));
    //2.3写各计算单元的子流域数据在输入文件中的偏移量
    fp.write(reinterpret_cast<const char *>(firse_offsets.data()), sizeof(OFFSET_TYPE) * processor_count);
    fp.flush();
    int offset = fp.tellg();
    //2.4写各计算单元上各子流域的数据
    for (int i = 0; i < processor_count; i++) {
        offset = fp.tellg();
        //2.4.1写i进程上需要处理的子流域总数目
        fp.write(reinterpret_cast<const char *>(&subbs_count_at_one_processor[i]), sizeof(SUBBASIN_ID_TYPE));
        //2.4.2写i号进程上各个子流域数据的相对偏移量
        fp.write(reinterpret_cast<const char *>(subb_offsets_at_diff_proc[i]->data()),
                 sizeof(OFFSET_TYPE) * subbs_count_at_one_processor[i]);
        //2.4.3写各个子流域数据
        for (int j = 0; j < subbs_count_at_one_processor[i]; j++) {
            //2.4.3.1写子流域ID
            SUBBASIN_ID_TYPE tmp = datas[i]->at(j)->subbasin_id;
            fp.write(reinterpret_cast<const char *>(&tmp), sizeof(SUBBASIN_ID_TYPE));
            //2.4.3.2写下游数目数目
            tmp = datas[i]->at(j)->down_subbasin_count;
            fp.write(reinterpret_cast<const char *>(&tmp), sizeof(SUBBASIN_ID_TYPE));
            //2.4.3.3写上游数目数目
            tmp = datas[i]->at(j)->up_subbasin_count;
            fp.write(reinterpret_cast<const char *>(&tmp), sizeof(SUBBASIN_ID_TYPE));
            //2.4.3.4写下游节点子流域ids
            fp.write(reinterpret_cast<const char *>(datas.at(i)->at(j)->down_subbasin_ids->data()),
                     sizeof(SUBBASIN_ID_TYPE) * datas[i]->at(j)->down_subbasin_count);
            //2.4.3.5写下游子流域所属进程
            fp.write(
                    reinterpret_cast<const char *>(datas.at(i)->at(j)->down_subbasin_belong_processor->data()),
                    sizeof(PROCESSOR_ID_TYPE) * datas[i]->at(j)->down_subbasin_count);
            //2.4.3.6写上游游节点子流域ids
            fp.write(reinterpret_cast<const char *>(datas.at(i)->at(j)->up_subbasin_ids->data()),
                     sizeof(SUBBASIN_ID_TYPE) * datas[i]->at(j)->up_subbasin_count);
            //2.4.3.7写上游子流域所属进程
            fp.write(reinterpret_cast<const char *>(datas.at(i)->at(j)->up_subbasin_belong_processor->data()),
                     sizeof(PROCESSOR_ID_TYPE) * datas[i]->at(j)->up_subbasin_count);
            //2.4.3.8写geo数据
            fp.write(reinterpret_cast<const char *>(datas[i]->at(j)->geo_data), sizeof(geo_info_subbasin));
            //2.4.3.8写soil数据
            fp.write(reinterpret_cast<const char *>(datas[i]->at(j)->soil_data), sizeof(soil_info_subbasin));
            //2.4.3.8写force数据
            fp.write(reinterpret_cast<const char *>(datas[i]->at(j)->force_data), sizeof(force_info_subbasin));
        }
        fp.flush();
    }
    fp.close();
}

TEST(morton_test_2, partition_read_test) {
    //测试生成输入文件
    if (kiwi::mpiUtils::ownRank == MASTER_PROCESSOR) {
        format_input_file();
    }
}

TEST(morton_test_3, partition_read_test) {
    //测试读取模块:流域输入文件名为input.bin,假设本进程在并行环境下的进程id为8
    read_subbasins_info obj_read_subbs("input.bin", 9);
    SUBBASINS_CONTAINER_TYPE *subbs_info = new SUBBASINS_CONTAINER_TYPE;
    // 测试读取8号进程上所有子流域的所有描述信息（**********内存允许？**************）
    obj_read_subbs.add_all_subbasins(*subbs_info, TAG_ALL_INFO);

    delete subbs_info;
}

TEST(morton_test_4, partition_read_test) {
    //测试读取模块:流域输入文件名为input.bin,本进程ID
    read_subbasins_info obj_read_subbs("input.bin", 9);
    SUBBASINS_CONTAINER_TYPE *subbs_info = new SUBBASINS_CONTAINER_TYPE;
    // 测试读取本进程上所有子流域的基本描述信息（**********内存允许？**************）
    obj_read_subbs.add_all_subbasins(*subbs_info, TAG_BASE_INFO);

    //(注意，本函数需要在在调用add_all_subbasins(*subbs_info, TAG_BASE_INFO)后才能被调用成功)
    // 然后测试一次性读取本进程上所有子流域的其他信息（geo、soil、force）
    obj_read_subbs.add_all_subbasins(*subbs_info, TAG_OTHER_INFO);

    delete subbs_info;
}

TEST(morton_test_5, partition_read_test) {
    //测试读取模块:流域输入文件名为input.bin,本进程ID
    read_subbasins_info obj_read_subbs("input.bin", 9);
    SUBBASINS_CONTAINER_TYPE *subbs_info = new SUBBASINS_CONTAINER_TYPE;
    // 测试读取本进程上所有子流域的基本描述信息（**********内存允许？**************）
    obj_read_subbs.add_all_subbasins(*subbs_info, TAG_BASE_INFO);

    //(注意，本函数需要在在调用add_all_subbasins(*subbs_info, TAG_BASE_INFO)后才能被调用成功)
    // 然后测试读依次取本进程上所有子流域的其他信息（geo、soil、force）
    obj_read_subbs.add_all_subbasins(*subbs_info, TAG_GEO_INFO);

    obj_read_subbs.add_all_subbasins(*subbs_info, TAG_SOIL_INFO);

    obj_read_subbs.add_all_subbasins(*subbs_info, TAG_FORCE_INFO);

    delete subbs_info;
}

TEST(morton_test_6, partition_read_test) {
    //测试读取模块:流域输入文件名为input.bin,本进程ID
    read_subbasins_info obj_read_subbs("input.bin", 9);
    //测试根据子流域ID，按需读取指定子流域各个部分的数据
    // 1.首先，需要获取本进程需要模拟的子流域的各个ID
    SUBBASIN_ID_CONTAINER_TYPE ids = obj_read_subbs.read_subbasin_all_ids();

    // 2.从ids里面按需选择需要读入的子流域数据
    SUBBASIN_ID_TYPE subb_id = ids.at(2);
    // 2.1 读入指定ID的all数据
    SUBBASIN_INFO_TYPE subb_info;
    obj_read_subbs.add_one_subasin(subb_id, subb_info, TAG_ALL_INFO);

    // 3 读入指定ID的base数据后再读入other
    SUBBASIN_INFO_TYPE subb_info1;
    obj_read_subbs.add_one_subasin(subb_id, subb_info1, TAG_BASE_INFO);
    obj_read_subbs.add_one_subasin(subb_id, subb_info1, TAG_OTHER_INFO);

    // 4 读入指定ID的base数据后再读入geo/soil/force数据
    SUBBASIN_INFO_TYPE subb_info2;
    obj_read_subbs.add_one_subasin(subb_id, subb_info2, TAG_BASE_INFO);
    obj_read_subbs.add_one_subasin(subb_id, subb_info2, TAG_GEO_INFO);
    obj_read_subbs.add_one_subasin(subb_id, subb_info2, TAG_SOIL_INFO);
    obj_read_subbs.add_one_subasin(subb_id, subb_info2, TAG_FORCE_INFO);
}

TEST(morton_test_7, partition_read_test) {
    //测试读取模块:流域输入文件名为input.bin,本进程ID
    read_subbasins_info obj_read_subbs("input.bin", 9);
    //测试根据子流域ID，按需读取指定子流域各个部分的数据
    // 1.首先，需要获取本进程需要模拟的子流域的各个ID
    SUBBASIN_ID_CONTAINER_TYPE ids = obj_read_subbs.read_subbasin_all_ids();

    // 2.从ids里面按需选择多个需要读入的子流域数据
    SUBBASIN_ID_CONTAINER_TYPE subb_ids(ids.data() + 1, ids.data() + 5);
    // 2.1 读入指定ID的all数据
    SUBBASINS_CONTAINER_TYPE subbs_info;
    obj_read_subbs.add_some_subasins(subb_ids, subbs_info, TAG_ALL_INFO);

    // 3 读入指定ID的base数据后再读入other
    SUBBASINS_CONTAINER_TYPE subbs_info1;
    obj_read_subbs.add_some_subasins(subb_ids, subbs_info1, TAG_BASE_INFO);
    obj_read_subbs.add_some_subasins(subb_ids, subbs_info1, TAG_OTHER_INFO);

    // 4 读入指定ID的base数据后再读入geo/soil/force数据
    SUBBASINS_CONTAINER_TYPE subbs_info2;
    obj_read_subbs.add_some_subasins(subb_ids, subbs_info2, TAG_BASE_INFO);
    obj_read_subbs.add_some_subasins(subb_ids, subbs_info2, TAG_GEO_INFO);
    obj_read_subbs.add_some_subasins(subb_ids, subbs_info2, TAG_SOIL_INFO);
    obj_read_subbs.add_some_subasins(subb_ids, subbs_info2, TAG_FORCE_INFO);
}

#endif //PNOHS_TEST_READ_SUBBASIN_INFO_H