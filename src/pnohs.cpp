//
// Created by genshen on 2017/12/24.
//

#include <utils/mpi_utils.h>
#include "pnohs.h"
#include "iostream"
#include "config_toml.h"

bool pnohs::beforeCreate() {
    // todo parse argv here.
    std::cout << "before create" << std::endl;
    return true;
};

// mpi has been initialized here.
void pnohs::onCreate() {
    configToml *pConfig;
    if (kiwi::mpiUtils::ownRank == MASTER_PROCESSOR) {
        std::cout << "mpi env was initialed." << std::endl;
        // initial config Obj, then read and resolve config file.
        pConfig = configToml::newInstance(
                "/home/genshen/Documents/workspace/CPlusPlus/hpc/pnohs/example/config.toml"); // todo config file from argv.
        if (pConfig->hasError) {
            std::cerr << "[Error] " << pConfig->errorMessage << std::endl;
            this->abort(2);
        }
    } else {
        // just initial a empty config Obj.
        pConfig = configToml::newInstance();
    }
    pConfig->sync(); // sync config data to other processors from master processor.
}

bool pnohs::prepare() {
    std::cout << "prepare" << std::endl;
    // todo decomposition here.
    return true;
}

void pnohs::onStart() {
    std::cout << "start" << std::endl;
}

void pnohs::beforeDestroy() {
    std::cout << "before destroy" << std::endl;
}

void pnohs::onFinish() {
    std::cout << "on finish" << std::endl;
}

void pnohs::onDestroy() {
    std::cout << "on destroy" << std::endl;
};