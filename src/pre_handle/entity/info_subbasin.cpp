//
// Created by wujiahao on 24/03/2018.
//
#include "info_subbasin.h"

info_subbasin::info_subbasin() : subbasin_id(0),
                                 down_subbasin_count(0), up_subbasin_count(0),
                                 up_subbasin_ids(nullptr),  //new SUBBASIN_ID_CONTAINER_TYPE;
                                 down_subbasin_ids(nullptr), //new SUBBASIN_ID_CONTAINER_TYPE;
                                 up_subbasin_belong_processor(nullptr), //new PROCESSOR_ID_CONTAINER_TYPE;
                                 down_subbasin_belong_processor(nullptr), //new PROCESSOR_ID_CONTAINER_TYPE;
                                 force_data(nullptr),
                                 soil_data(nullptr),
                                 geo_data(nullptr) {
}

info_subbasin::info_subbasin(SUBBASIN_ID_TYPE subbasinId, SUBBASIN_COUNT_TYPE upstreamCount,
                             SUBBASIN_COUNT_TYPE downstreamCount) :
        subbasin_id(subbasinId), up_subbasin_count(upstreamCount), down_subbasin_count(downstreamCount) {
    down_subbasin_ids = new SUBBASIN_ID_CONTAINER_TYPE;
    down_subbasin_belong_processor = new PROCESSOR_ID_CONTAINER_TYPE;
    up_subbasin_ids = new SUBBASIN_ID_CONTAINER_TYPE;
    up_subbasin_belong_processor = new PROCESSOR_ID_CONTAINER_TYPE;
}

info_subbasin::~info_subbasin() {
    delete (this->up_subbasin_ids);
    delete (this->down_subbasin_ids);
    delete (this->down_subbasin_belong_processor);
    delete (this->up_subbasin_belong_processor);

    delete (this->force_data);
    delete (this->soil_data);
    delete (this->geo_data);
}

void info_subbasin::setUp_subbasin_count(unsigned int up_subbasin_count) {
    this->up_subbasin_count = up_subbasin_count;
}

void info_subbasin::setSubbasin_id(SUBBASIN_ID_TYPE subbasin_id) {
    this->subbasin_id = subbasin_id;
}

void info_subbasin::setUp_subbasin_ids(std::vector<unsigned long> *up_subbasin_ids) {
    this->up_subbasin_ids = up_subbasin_ids;
}

void info_subbasin::setUp_subbasin_belong_processor(std::vector<unsigned long> *up_subbasin_belong_processor) {
    this->up_subbasin_belong_processor = up_subbasin_belong_processor;
}

void info_subbasin::setDown_subbasin_ids(std::vector<unsigned long> *down_subbasin_ids) {
    this->down_subbasin_ids = down_subbasin_ids;
}

void info_subbasin::setDown_subbasin_belong_processor(std::vector<unsigned long> *down_subbasin_belong_processor) {
    this->down_subbasin_belong_processor = down_subbasin_belong_processor;
}

void info_subbasin::setGeo_data(geo_info_subbasin *geo_data) {
    this->geo_data = geo_data;
}

void info_subbasin::setSoil_data(soil_info_subbasin *soil_data) {
    this->soil_data = soil_data;
}

void info_subbasin::setForce_data(force_info_subbasin *force_data) {
    this->force_data = force_data;
}
