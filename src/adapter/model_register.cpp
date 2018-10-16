//
// Created by genshen $EMAIL on 10/16/18.
//

#include "model_register.h"

RunoffAdapter *ModelRegister::RunoffInterface::newInstance(const _type_model_key key) {
    throw std::invalid_argument("you must implement interface newInstanceRunoff.");
}

RoutingAdapter *ModelRegister::RoutingInterface::newInstance(const _type_model_key key) {
    throw std::invalid_argument("you must implement interface newInstanceRouting.");
}

// for runoff models

static void ModelRegister::registerRunoffModel(const _type_model_key key, RunoffInstanceInterface model) {
    runoffNest.insert({key, model});
}

static void ModelRegister::unRegisterRunoffModel(const _type_model_key key) {
    runoffNest.erase(key);
}

static void ModelRegister::unRegisterAllRunoffModels() {
    runoffNest.clear();
}

static RunoffAdapter *ModelRegister::newInstanceRunoff(const _type_model_key key) {
    auto it = runoffNest.find(key); // std::map<_type_model_key, RunoffInstanceInterface>::iterator
    if (it != runoffNest.end()) {
        return nullptr;
    }
    RunoffInstanceInterface func =  (*it).second;
    return (*func)(key);
}

// for routing models

static void ModelRegister::registerRoutingModel(const _type_model_key key, RoutingInstanceInterface model) {
    routingNest.insert({key, model});
}

static void ModelRegister::unRegisterRoutingModel(const _type_model_key key) {
    routingNest.erase(key);
}

static void ModelRegister::unRegisterAllRoutingModels() {
    routingNest.clear();
}

static RoutingAdapter *ModelRegister::newInstanceRouting(const _type_model_key key) {
    auto it = routingNest.find(key); // std::map<_type_model_key, RunoffInstanceInterface>::iterator
    if (it != routingNest.end()) {
        return nullptr;
    }
    RoutingInstanceInterface func =  (*it).second;
    return (*func)(key);
}

// for both types models.

static void ModelRegister::unRegisterAll() {
    unRegisterAllRunoffModels();
    unRegisterAllRoutingModels();
}
