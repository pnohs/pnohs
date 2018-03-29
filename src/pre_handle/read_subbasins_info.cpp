//
// Created by wujiahao on 24/03/2018.
//

#include "read_subbasins_info.h"
#include <fstream>
#include <iostream>

read_subbasins_info::read_subbasins_info(const std::string &filename, const PROCESSOR_ID_TYPE self_processor_id)
{
    dao_rsi.init(filename,self_processor_id);
}

const SUBBASIN_ID_CONTAINER_TYPE &read_subbasins_info::read_subbasin_all_ids()
{
    return this->dao_rsi.getSubbasin_ids();
}

void read_subbasins_info::add_all_subbasins(SUBBASINS_CONTAINER_TYPE &subbasins, int tag)
{
   switch(tag){
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
           break;
       case TAG_SOIL_INFO:
           break;
       case TAG_FORCE_INFO:
           break;
       default:
           err_handle::sys_err("not this tag in read subbasin info", -2);
   }
}

SUBBASIN_ID_TYPE read_subbasins_info::get_subbasins_count() {

    return dao_rsi.getSubbasins_count();

}

