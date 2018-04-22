//
// Created by genshen on 3/23/18.
//

#include <iostream>
#include "config_toml.h"

// initial pointer of ConfigToml.
ConfigToml *ConfigToml::pConfigInstance = nullptr;

ConfigToml::ConfigToml() : kiwi::config::config() {

}

ConfigToml *ConfigToml::getInstance() {
    if (pConfigInstance == nullptr) {
        pConfigInstance = new ConfigToml(); // todo delete after not usable.
    }
    return pConfigInstance; // make sure there is a configure instance.
}

ConfigToml *ConfigToml::newInstance(const std::string &configureFilePath) {
    if (pConfigInstance == nullptr) {
        pConfigInstance = new ConfigToml(); // todo delete.
        pConfigInstance->resolve(configureFilePath);
    }
    return pConfigInstance;
}

// @override only for master processor.
// @see https://github.com/skystrife/cpptoml#example-usage for more details.
void ConfigToml::resolveConfig(std::shared_ptr<cpptoml::table> config) { // todo change paarm name("config" is not allow).
    // dispatch section.
    auto confDispatch = config->get_table("dispatch");
    dispatchFilePath = confDispatch->get_as<std::string>("dispatch_file").value_or("pnohs.dis"); // todo * get_as??

    // simulation section
    auto confSimulation = config->get_table("simulation");
    simulationTimeSteps = (unsigned long) confSimulation->get_as<int64_t>("time_steps").value_or(0);
}

// @override
void ConfigToml::putConfigData(kiwi::Bundle &bundle) {
    bundle.put(MPI_COMM_WORLD, dispatchFilePath);
    bundle.put(MPI_COMM_WORLD, simulationTimeSteps);
}

// @override
void ConfigToml::getConfigData(kiwi::Bundle &bundle) {
    int cursor = 0;
    bundle.get(MPI_COMM_WORLD, cursor, dispatchFilePath);
    bundle.get(MPI_COMM_WORLD, cursor, simulationTimeSteps);
}
