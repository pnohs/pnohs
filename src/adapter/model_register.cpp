//
// Created by genshen $EMAIL on 10/16/18.
//

#include "model_register.h"

std::map<_type_model_id, ModelRegister::RunoffInstanceInterface> ModelRegister::runoffNest;
std::map<_type_model_id, ModelRegister::RoutingInstanceInterface> ModelRegister::routingNest;
std::map<_type_model_key, _type_model_id> ModelRegister::id_key_map;
const _type_model_id ModelRegister::MODEL_ID_NULL = 0;

RunoffAdapter *ModelRegister::RunoffInterface::newInstance() {
    throw std::invalid_argument("you must implement interface newInstanceRunoff.");
}

RoutingAdapter *ModelRegister::RoutingInterface::newInstance() {
    throw std::invalid_argument("you must implement interface newInstanceRouting.");
}

// for runoff models

_type_model_id ModelRegister::registerRunoffModel(const _type_model_key key, RunoffInstanceInterface model) {
    _type_model_id id = generateModelId();
    id_key_map.insert({key, id});
    runoffNest.insert({id, model});
    return id;
}

void ModelRegister::unRegisterRunoffModel(const _type_model_id id) {
    runoffNest.erase(id);
    eraseIdKeyMapById(id);
};

void ModelRegister::unRegisterAllRunoffModels() {
    // std::map<_type_model_id, RunoffInstanceInterface>::iterator it
    for (auto &it : runoffNest) {
        eraseIdKeyMapById(it.first);
    }
    runoffNest.clear();
}

RunoffAdapter *ModelRegister::newInstanceRunoff(const _type_model_id id) {
    auto it = runoffNest.find(id); // std::map<_type_model_id, RunoffInstanceInterface>::iterator
    if (it == runoffNest.end()) {
        return nullptr;
    }
    RunoffInstanceInterface func = (*it).second;
    return (*func)();
}

// for routing models

_type_model_id ModelRegister::registerRoutingModel(const _type_model_key key, RoutingInstanceInterface model) {
    _type_model_id id = generateModelId();
    id_key_map.insert({key, id});
    routingNest.insert({id, model});
    return id;
}

void ModelRegister::unRegisterRoutingModel(const _type_model_id id) {
    routingNest.erase(id);
    eraseIdKeyMapById(id);
}

void ModelRegister::unRegisterAllRoutingModels() {
    // when deleting ids of routing models in id_key_map,
    // there are double for loops.
    // It may have no bad effect if the count of models is not too many.
    for (auto &it : routingNest) {
        eraseIdKeyMapById(it.first);
    }
    routingNest.clear();
}

RoutingAdapter *ModelRegister::newInstanceRouting(const _type_model_id id) {
    auto it = routingNest.find(id); // std::map<_type_model_id, RunoffInstanceInterface>::iterator
    if (it == routingNest.end()) {
        return nullptr;
    }
    RoutingInstanceInterface func = (*it).second;
    return (*func)();
}

// for both types models.

void ModelRegister::unRegisterAll() {
    unRegisterAllRunoffModels();
    unRegisterAllRoutingModels();
}

_type_model_id ModelRegister::getModelIdByKey(const _type_model_key key) {
    auto it = id_key_map.find(key);
    if (it != id_key_map.end()) {
        return it->second;
    }
    return MODEL_ID_NULL;
}

_type_model_id ModelRegister::generateModelId() {
    static _type_model_id unique_id = 0;
    unique_id++;
    return unique_id;
}

void ModelRegister::eraseIdKeyMapById(const _type_model_id id) {
    std::map<_type_model_key, _type_model_id>::iterator it;
    for (it = id_key_map.begin(); it != id_key_map.end(); it++) {
        if (it->second == id) {
            it = id_key_map.erase(it);
            break;
        }
    }
}
