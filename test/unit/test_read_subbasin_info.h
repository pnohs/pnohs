//
// Created by wujiahao on 26/03/2018.
//

#ifndef PNOHS_TEST_READ_SUBBASIN_INFO_H
#define PNOHS_TEST_READ_SUBBASIN_INFO_H

#include <gtest/gtest.h>
#include <fstream>
#include <pre_handle/read_subbasins_info.h>
#include "../../src/pre_handle/entity/info_subbasin.h"

class test_read_subbasin_info_env:public ::testing::Environment{
public:

    void SetUp() override {
        Environment::SetUp();

        //1.构造数据
        format_input_file();

        //2.测试读取模块:流域输入文件名为input.bin,假设本进程在并行环境下的进程id为8
        read_subbasins_info obj_read_subbs("input.bin",8);
        SUBBASINS_CONTAINER_TYPE *subbs_info = new SUBBASINS_CONTAINER_TYPE;

        //2.1测试读取8号进程上所有子流域的所有描述信息（**********内存允许？**************）
        //obj_read_subbs.add_all_subbasins(*subbs_info,TAG_ALL_INFO);

        // 2.2测试读取8号进程上所有子流域的基本信息（描述河网拓扑结构的信息）
        obj_read_subbs.add_all_subbasins(*subbs_info,TAG_BASE_INFO);
        // 2.2.1测试读取8号进程上所有子流域的基本信息（描述河网拓扑结构的信息）,后再读取这些子流域的其他描述信息
        obj_read_subbs.add_all_subbasins(*subbs_info,TAG_OTHER_INFO);


    }

    void TearDown() override {
        Environment::TearDown();
    }



    /**
     * 该方法生成测试用的子流域数据
     */
    void format_input_file(){
        PROCESSOR_ID_TYPE processor_count = 10;
        std::vector<SUBBASIN_ID_TYPE> subbs_count_at_one_processor;
        std::vector<std::vector<info_subbasin *> *> datas;
        std::vector<std::vector<OFFSET_TYPE> *> subb_offsets_at_diff_proc;
        std::vector<OFFSET_TYPE> all_subb_size_on_diff_proc;
        all_subb_size_on_diff_proc.resize(processor_count,0);

        for(int i=0; i<processor_count; i++){

            std::vector<info_subbasin *> *tmp_data = new std::vector<info_subbasin *>;
            std::vector<OFFSET_TYPE> * tmp_subb_offsets = new std::vector<OFFSET_TYPE>;
            subbs_count_at_one_processor.push_back(i+1);
            tmp_subb_offsets->resize(subbs_count_at_one_processor[i]);

            OFFSET_TYPE pre_subb_data_size = 0;
            for(int j=0; j<subbs_count_at_one_processor[i]; j++){
                info_subbasin *tmp_subb = new info_subbasin;

                tmp_subb->setSubbasin_id(j+3);
                tmp_subb->setDown_subbasin_count(j*(i+1));
                tmp_subb->setDown_subbasin_ids(new SUBBASIN_ID_CONTAINER_TYPE);
                tmp_subb->setDown_subbasin_belong_processor(new PROCESSOR_ID_CONTAINER_TYPE);
                for(int k=0; k<tmp_subb->getDown_subbasin_count(); k++)
                {
                    tmp_subb->getDown_subbasin_ids()->push_back(k+j);
                    tmp_subb->getDown_subbasin_belong_processor()->push_back(i+k);
                }

                tmp_subb->setUp_subbasin_count(j+i+1);
                tmp_subb->setUp_subbasin_ids(new SUBBASIN_ID_CONTAINER_TYPE);
                tmp_subb->setUp_subbasin_belong_processor(new PROCESSOR_ID_CONTAINER_TYPE);
                for(int k=0; k<tmp_subb->getUp_subbasin_count(); k++)
                {
                    tmp_subb->getUp_subbasin_ids()->push_back(k+i);
                    tmp_subb->getUp_subbasin_belong_processor()->push_back(i+k);
                }

                tmp_subb->setGeo_data(new geo_info_subbasin);
                tmp_subb->getGeo_data()->elev = 200.8+j+i;
                tmp_subb->getGeo_data()->lat = 127.8+i+j;
                tmp_subb->getGeo_data()->lon = 80.8+i+j;

                tmp_subb->setForce_data(new force_info_subbasin);
                tmp_subb->getForce_data()->air_tmp = 24.8+i+j;

                tmp_subb->setSoil_data(new soil_info_subbasin);
                tmp_subb->getSoil_data()->soil_layers = 10;

                tmp_data->push_back(tmp_subb);

                if(j == 0)
                    tmp_subb_offsets->at(j) = pre_subb_data_size;
                else
                    tmp_subb_offsets->at(j) = pre_subb_data_size + tmp_subb_offsets->at(j-1);

                pre_subb_data_size = sizeof(tmp_subb->getSubbasin_id())
                                     + sizeof(tmp_subb->getUp_subbasin_count())
                                     + sizeof(tmp_subb->getDown_subbasin_count())
                                     + sizeof(SUBBASIN_ID_TYPE)*tmp_subb->getDown_subbasin_count() + sizeof(PROCESSOR_ID_TYPE)*tmp_subb->getDown_subbasin_count()
                                     + sizeof(SUBBASIN_ID_TYPE)*tmp_subb->getUp_subbasin_count() + sizeof(PROCESSOR_ID_TYPE)*tmp_subb->getUp_subbasin_count()
                                     + sizeof(tmp_subb->getGeo_data()->lon) + sizeof(tmp_subb->getGeo_data()->lat) + sizeof(tmp_subb->getGeo_data()->elev)
                                     + sizeof(tmp_subb->getSoil_data()->soil_layers)
                                     + sizeof(tmp_subb->getForce_data()->air_tmp);

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
        firse_offsets[0] = sizeof(PROCESSOR_ID_TYPE) + processor_count*sizeof(OFFSET_TYPE);
        for(int i=1;i<processor_count;i++){
            firse_offsets[i] = firse_offsets[i-1] + all_subb_size_on_diff_proc[i-1]
                               + sizeof(SUBBASIN_ID_TYPE)
                               + subbs_count_at_one_processor[i-1]* sizeof(OFFSET_TYPE);
        }
        //2.2写计算单元数
        fp.write(reinterpret_cast<const char *>(&processor_count), sizeof(processor_count));
        //2.3写各计算单元的子流域数据在输入文件中的偏移量
        fp.write(reinterpret_cast<const char *>(firse_offsets.data()), sizeof(OFFSET_TYPE) * processor_count);
        fp.flush();
        int foot = fp.tellp();
        //2.4写各计算单元上各子流域的数据
        for(int i=0;i<processor_count;i++)
        {
            foot = fp.tellp();
            //2.4.1写i进程上需要处理的子流域总数目
            fp.write(reinterpret_cast<const char *>(&subbs_count_at_one_processor[i]), sizeof(SUBBASIN_ID_TYPE));
            //2.4.2写i号进程上各个子流域数据的相对偏移量
            fp.write(reinterpret_cast<const char *>(subb_offsets_at_diff_proc[i]->data()), sizeof(OFFSET_TYPE) * subbs_count_at_one_processor[i]);
            //2.4.3写各个子流域数据
            foot = fp.tellp();

            for(int j=0;j<subbs_count_at_one_processor[i];j++)
            {
                foot = fp.tellp();
                //2.4.3.1写子流域ID
                SUBBASIN_ID_TYPE tmp = datas[i]->at(j)->getSubbasin_id();
                fp.write(reinterpret_cast<const char *>(&tmp), sizeof(SUBBASIN_ID_TYPE));
                //2.4.3.2写下游数目数目
                tmp = datas[i]->at(j)->getDown_subbasin_count();
                fp.write(reinterpret_cast<const char *>(&tmp), sizeof(SUBBASIN_ID_TYPE));
                //2.4.3.3写上游数目数目
                tmp = datas[i]->at(j)->getUp_subbasin_count();
                fp.write(reinterpret_cast<const char *>(&tmp), sizeof(SUBBASIN_ID_TYPE));
                foot = fp.tellp();
                //2.4.3.4写下游节点子流域ids
                fp.write(reinterpret_cast<const char *>(datas.at(i)->at(j)->getDown_subbasin_ids()->data()),
                         sizeof(SUBBASIN_ID_TYPE) * datas[i]->at(j)->getDown_subbasin_count());
                foot = fp.tellp();
                //2.4.3.5写下游子流域所属进程
                fp.write(reinterpret_cast<const char *>(datas.at(i)->at(j)->getDown_subbasin_belong_processor()->data()),
                         sizeof(PROCESSOR_ID_TYPE) * datas[i]->at(j)->getDown_subbasin_count());
                foot = fp.tellp();
                //2.4.3.6写上游游节点子流域ids
                fp.write(reinterpret_cast<const char *>(datas.at(i)->at(j)->getUp_subbasin_ids()->data()),
                         sizeof(SUBBASIN_ID_TYPE) * datas[i]->at(j)->getUp_subbasin_count());
                foot = fp.tellp();
                //2.4.3.7写上游子流域所属进程
                fp.write(reinterpret_cast<const char *>(datas.at(i)->at(j)->getUp_subbasin_belong_processor()->data()),
                         sizeof(PROCESSOR_ID_TYPE) * datas[i]->at(j)->getUp_subbasin_count());
                foot = fp.tellp();
                //2.4.3.8写geo数据
                //fp.write(reinterpret_cast<const char *>(datas[i]->at(j)->getGeo_data()), sizeof(geo_info_subbasin));
                fp.write(reinterpret_cast<const char *>(&datas[i]->at(j)->getGeo_data()->lat), sizeof(datas[i]->at(j)->getGeo_data()->lat));
                fp.write(reinterpret_cast<const char *>(&datas[i]->at(j)->getGeo_data()->lon), sizeof(datas[i]->at(j)->getGeo_data()->lon));
                fp.write(reinterpret_cast<const char *>(&datas[i]->at(j)->getGeo_data()->elev), sizeof(datas[i]->at(j)->getGeo_data()->elev));
                foot = fp.tellp();
                //2.4.3.8写soil数据
                //fp.write(reinterpret_cast<const char *>(datas[i]->at(j)->getSoil_data()), sizeof(soil_info_subbasin));
                fp.write(reinterpret_cast<const char *>(&datas[i]->at(j)->getSoil_data()->soil_layers), sizeof(datas[i]->at(j)->getSoil_data()->soil_layers));
                foot = fp.tellp();
                //2.4.3.8写force数据
                //fp.write(reinterpret_cast<const char *>(datas[i]->at(j)->getForce_data()), sizeof(force_info_subbasin));
                fp.write(reinterpret_cast<const char *>(&datas[i]->at(j)->getForce_data()->air_tmp), sizeof(datas[i]->at(j)->getForce_data()->air_tmp));
                foot = fp.tellp();
            }
            fp.flush();
        }
        fp.close();
    }

};

#endif //PNOHS_TEST_READ_SUBBASIN_INFO_H
