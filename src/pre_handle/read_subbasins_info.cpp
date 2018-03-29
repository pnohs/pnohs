//
// Created by wujiahao on 24/03/2018.
//

#include "read_subbasins_info.h"
#include <fstream>
#include <iostream>

read_subbasins_info::read_subbasins_info(const std::string &filename, const PROCESSOR_ID_TYPE self_processor_id) {
    dao_rsi.init(filename, self_processor_id);
}

const SUBBASIN_ID_CONTAINER_TYPE &read_subbasins_info::read_subbasin_all_ids() {
    return this->dao_rsi.getSubbasin_ids();
}

void read_subbasins_info::add_all_subbasins(SUBBASINS_CONTAINER_TYPE &subbasins, int tag) {
    switch (tag) {
        case TAG_ALL_INFO:
            this->dao_rsi.read_subbasins_allinfo_all(subbasins);
            break;
        case TAG_BASE_INFO:
            this->dao_rsi.read_subbasins_baseinfo_all(subbasins);
            break;
        case TAG_OTHER_INFO:
            this->dao_rsi.read_subbasins_otherinfo_all(subbasins);
            break;
        case TAG_GEO_INFO:
            this->dao_rsi.read_subbasins_geoinfo_all(subbasins);
            break;
        case TAG_SOIL_INFO:
            this->dao_rsi.read_subbasins_soilinfo_all(subbasins);
            break;
        case TAG_FORCE_INFO:
            this->dao_rsi.read_subbasins_forceinfo_all(subbasins);
            break;
        default:
            err_handle::sys_err("not this tag in read subbasin info", -2);
    }
}

SUBBASIN_ID_TYPE read_subbasins_info::get_subbasins_count() {
    return dao_rsi.getSubbasins_count();
}

void read_subbasins_info::add_one_subasin(const unsigned long subbasin_id, info_subbasin &subb_info, int tag) {

    switch (tag) {
        case TAG_ALL_INFO:
            this->dao_rsi.read_subbasin_allinfo_byid(subbasin_id, subb_info);
            break;
        case TAG_BASE_INFO:
            this->dao_rsi.read_subbasin_baseinfo_byid(subbasin_id, subb_info);
            break;
        case TAG_OTHER_INFO:
            this->dao_rsi.read_subbasin_otherinfo_byid(subbasin_id, subb_info);
            break;
        case TAG_GEO_INFO:
            this->dao_rsi.read_subbasin_geoinfo_byid(subbasin_id, subb_info);
            break;
        case TAG_SOIL_INFO:
            this->dao_rsi.read_subbasin_soilinfo_byid(subbasin_id, subb_info);
            break;
        case TAG_FORCE_INFO:
            this->dao_rsi.read_subbasin_forceinfo_byid(subbasin_id, subb_info);
            break;
        default:
            err_handle::sys_err("not this tag in read subbasin info", -2);
    }
}

void read_subbasins_info::add_some_subasins(const SUBBASIN_ID_CONTAINER_TYPE &subbasin_ids,
                                            SUBBASINS_CONTAINER_TYPE &subbasins, int tag) {
    for (int i = 0; i < subbasin_ids.size(); i++) {
        if (subbasins.find(subbasin_ids.at(i)) == subbasins.end());
        {
            subbasins.insert(SUBBASINS_CONTAINER_TYPE::value_type(subbasin_ids[i], new SUBBASIN_INFO_TYPE));
        }

        this->add_one_subasin(subbasin_ids[i], *subbasins.at(subbasin_ids[i]), tag);
    }
}


