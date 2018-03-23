//
// Created by genshen on 3/23/18.
//

#include <iostream>
#include "config_toml.h"

// initial pointer of configToml.
configToml *configToml::pConfigInstance = nullptr;

configToml::configToml() : kiwi::config::config() {

}

configToml *configToml::newInstance() {
    if (pConfigInstance == nullptr) {
        pConfigInstance = new configToml();
    }
    return pConfigInstance; // make sure there is a configure instance.
}

configToml *configToml::newInstance(const std::string &configureFilePath) {
    if (pConfigInstance == nullptr) {
        pConfigInstance = new configToml();
        pConfigInstance->resolve(configureFilePath);
    }
    return pConfigInstance;
}

// @override only for master processor.
void configToml::resolveConfig(std::shared_ptr<cpptoml::table> table) {
    Filename = "filename";
}

// @override
void configToml::putConfigData(kiwi::Bundle &bundle) {
    bundle.put(MPI_COMM_WORLD, Filename);
}

// @override
void configToml::getConfigData(kiwi::Bundle &bundle) {
    int cursor = 0;
    bundle.get(MPI_COMM_WORLD, cursor, Filename);
}