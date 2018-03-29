//
// Created by wujiahao on 24/03/2018.
//
#include "info_subbasin.h"

info_subbasin::info_subbasin()
{
    // 不该在此初始化，应该初次用时实例化(new)
    this->force_data = nullptr;
    this->geo_data = nullptr;
    this->soil_data = nullptr;

    this->down_subbasin_ids = nullptr; //new SUBBASIN_ID_CONTAINER_TYPE;
    this->up_subbasin_ids = nullptr;  //new SUBBASIN_ID_CONTAINER_TYPE;
    this->down_subbasin_belong_processor = nullptr; //new PROCESSOR_ID_CONTAINER_TYPE;
    this->up_subbasin_belong_processor = nullptr; //new PROCESSOR_ID_CONTAINER_TYPE;

    this->subbasin_id = 0;
    this->down_subbasin_count = 0;
    this->up_subbasin_count = 0;
}

info_subbasin::~info_subbasin()
{
    delete(this->force_data);
    delete(this->soil_data);
    delete(this->geo_data);

    delete(this->up_subbasin_ids);
    delete(this->down_subbasin_ids);
    delete(this->down_subbasin_belong_processor);
    delete(this->up_subbasin_belong_processor);
}

SUBBASIN_ID_TYPE info_subbasin::getUp_subbasin_count() const {
    return up_subbasin_count;
}

void info_subbasin::setUp_subbasin_count(unsigned int up_subbasin_count) {
    info_subbasin::up_subbasin_count = up_subbasin_count;
}

std::vector<unsigned long> *info_subbasin::getUp_subbasin_ids() const {
    return up_subbasin_ids;
}

SUBBASIN_ID_TYPE info_subbasin::getDown_subbasin_count() const {
    return down_subbasin_count;
}

void info_subbasin::setDown_subbasin_count(unsigned int down_subbasin_count) {
    info_subbasin::down_subbasin_count = down_subbasin_count;
}

std::vector<unsigned long> *info_subbasin::getDown_subbasin_ids() const {
    return down_subbasin_ids;
}


geo_info_subbasin *info_subbasin::getGeo_data() const {
    return geo_data;
}


soil_info_subbasin *info_subbasin::getSoil_data() const {
    return soil_data;
}


force_info_subbasin *info_subbasin::getForce_data() const {
    return force_data;
}

std::vector<unsigned long> *info_subbasin::getUp_subbasin_belong_processor() const {
    return up_subbasin_belong_processor;
}

std::vector<unsigned long> *info_subbasin::getDown_subbasin_belong_processor() const {
    return down_subbasin_belong_processor;
}

void info_subbasin::setSubbasin_id(SUBBASIN_ID_TYPE subbasin_id) {
    this->subbasin_id = subbasin_id;
}

SUBBASIN_ID_TYPE info_subbasin::getSubbasin_id() const {
    return this->subbasin_id;
}

void info_subbasin::setGeo_data(geo_info_subbasin *geo_data) {
    info_subbasin::geo_data = geo_data;
}

void info_subbasin::setSoil_data(soil_info_subbasin *soil_data) {
    info_subbasin::soil_data = soil_data;
}

void info_subbasin::setForce_data(force_info_subbasin *force_data) {
    info_subbasin::force_data = force_data;
}

void info_subbasin::setUp_subbasin_ids(std::vector<unsigned long> *up_subbasin_ids) {
    info_subbasin::up_subbasin_ids = up_subbasin_ids;
}

void info_subbasin::setUp_subbasin_belong_processor(std::vector<unsigned long> *up_subbasin_belong_processor) {
    info_subbasin::up_subbasin_belong_processor = up_subbasin_belong_processor;
}

void info_subbasin::setDown_subbasin_ids(std::vector<unsigned long> *down_subbasin_ids) {
    info_subbasin::down_subbasin_ids = down_subbasin_ids;
}

void info_subbasin::setDown_subbasin_belong_processor(std::vector<unsigned long> *down_subbasin_belong_processor) {
    info_subbasin::down_subbasin_belong_processor = down_subbasin_belong_processor;
}


