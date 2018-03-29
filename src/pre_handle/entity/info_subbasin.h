//
// Created by wujiahao on 24/03/2018.
//

#ifndef PNOHS_INFO_SUBBASIN_H
#define PNOHS_INFO_SUBBASIN_H

#include "geo_info_subbasin.h"
#include "soil_info_subbasin.h"
#include "force_info_subbasin.h"
#include "../constant.h"

/**
 * all infomation of a subbasion node needed by simmulation
 */

class info_subbasin {

public:
    info_subbasin();

    ~info_subbasin();

    SUBBASIN_ID_TYPE getSubbasin_id() const;

    void setSubbasin_id(SUBBASIN_ID_TYPE subbasin_id);

    SUBBASIN_ID_TYPE getUp_subbasin_count() const;

    void setUp_subbasin_count(unsigned int up_subbasin_count);

    std::vector<unsigned long> *getUp_subbasin_ids() const;

    SUBBASIN_ID_TYPE getDown_subbasin_count() const;

    void setDown_subbasin_count(unsigned int down_subbasin_count);

    std::vector<unsigned long> *getDown_subbasin_ids() const;

    geo_info_subbasin *getGeo_data() const;

    void setGeo_data(geo_info_subbasin *geo_data);

    void setSoil_data(soil_info_subbasin *soil_data);

    void setForce_data(force_info_subbasin *force_data);

    soil_info_subbasin *getSoil_data() const;

    std::vector<unsigned long> *getUp_subbasin_belong_processor() const;

    std::vector<unsigned long> *getDown_subbasin_belong_processor() const;

    force_info_subbasin *getForce_data() const;


    void setUp_subbasin_ids(std::vector<unsigned long> *up_subbasin_ids);

    void setUp_subbasin_belong_processor(std::vector<unsigned long> *up_subbasin_belong_processor);

    void setDown_subbasin_ids(std::vector<unsigned long> *down_subbasin_ids);

    void setDown_subbasin_belong_processor(std::vector<unsigned long> *down_subbasin_belong_processor);

private:
    SUBBASIN_ID_TYPE subbasin_id;                //the id of a subbasion after division
    SUBBASIN_COUNT_TYPE up_subbasin_count;          //Number of subbasins upstream of the subbasin
    SUBBASIN_ID_CONTAINER_TYPE *up_subbasin_ids;     //the ids of subbasins upstream of the subbasin
    PROCESSOR_ID_CONTAINER_TYPE *up_subbasin_belong_processor;
    SUBBASIN_COUNT_TYPE down_subbasin_count;        //Number of subbasins downstream of the subbasin
    SUBBASIN_ID_CONTAINER_TYPE *down_subbasin_ids;   //ids of subbasins downupstream of the subbasin
    PROCESSOR_ID_CONTAINER_TYPE *down_subbasin_belong_processor;

    geo_info_subbasin *geo_data; //the geographical data of the subbasin
    soil_info_subbasin *soil_data;                  //the soil data of the subbasin
    force_info_subbasin *force_data;                 //the atosphere data of the subbasin
};


#endif //PNOHS_INFO_SUBBASIN_H
