//
// Created by genshen on 3/23/18.
//

#include <iostream>
#include "config_toml.h"

// initial pointer of ConfigToml.
ConfigToml *ConfigToml::pConfigInstance = nullptr;

ConfigToml::ConfigToml() : kiwi::config::config() {

}

ConfigToml *ConfigToml::newInstance() {
    if (pConfigInstance == nullptr) {
        pConfigInstance = new ConfigToml();
    }
    return pConfigInstance; // make sure there is a configure instance.
}

ConfigToml *ConfigToml::newInstance(const std::string &configureFilePath) {
    if (pConfigInstance == nullptr) {
        pConfigInstance = new ConfigToml();
        pConfigInstance->resolve(configureFilePath);
    }
    return pConfigInstance;
}

// @override only for master processor.
void ConfigToml::resolveConfig(std::shared_ptr<cpptoml::table> table) {
    Filename = "filename";
}

// @override
void ConfigToml::putConfigData(kiwi::Bundle &bundle) {
    bundle.put(MPI_COMM_WORLD, Filename);
}

// @override
void ConfigToml::getConfigData(kiwi::Bundle &bundle) {
    int cursor = 0;
    bundle.get(MPI_COMM_WORLD, cursor, Filename);
}