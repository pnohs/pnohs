//
// Created by genshen on 2017/12/24.
//

#include <utils/mpi_utils.h>
#include <argagg.hpp>
#include "pnohs.h"
#include "iostream"
#include "partition_parse.h"

bool pnohs::beforeCreate(int argc, char *argv[]) {
    // parse arguments using lib args: https://github.com/vietjtnguyen/argagg.
    argagg::parser argparser{{
                                     {"help", {"-h", "--help"}, "shows this help message", 0},
                                     {"version", {"-v", "--version"}, "show package version", 0},
                                     {"config", {"-c", "--conf"}, "path of configure file", 1},
                             }};

    argagg::parser_results args;
    try {
        args = argparser.parse(argc, argv);
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return false;
    }

    if (args["help"]) {
        argagg::fmt_ostream fmt(std::cerr);
        fmt << "Usage: pnohs [options]" << std::endl // todo change program name.
            << argparser;
        return false;
    }

    if (args["version"]) {
        argagg::fmt_ostream fmt(std::cerr);
        fmt << "version 0.1.0" << std::endl
            << "Copyright (C) 2017 USTB" << std::endl;
        return false;
    }

    configFilePath = args["config"].as<std::string>("config.toml");
    return true;
};

// mpi has been initialized here.
void pnohs::onCreate() {
    ConfigToml *pConfig;
    if (kiwi::mpiUtils::ownRank == MASTER_PROCESSOR) {
        std::cout << "mpi env was initialed." << std::endl;
        // initial config Obj, then read and resolve config file.
        pConfig = ConfigToml::newInstance(configFilePath); // todo config file from argv.
        if (pConfig->hasError) {
            std::cerr << "[Error] " << pConfig->errorMessage << std::endl;
            this->abort(2);
        }
    } else {
        // just initial a empty config Obj.
        pConfig = ConfigToml::newInstance();
    }
    pConfig->sync(); // sync config data to other processors from master processor.

}

bool pnohs::prepare() {
    // new simulation instance.
    mSimulation = new Simulation();
    // initial river nodes and their upstream/downstream.
    mSimulation->setupNodes();
//    initialNodes(nodes); // 初始化各结点，及其上下游关系(记录各结点的上下游都是哪些结点)
//    loadData(nodes);     // 根据结点加载模拟需要的数据(如地理信息数据、河段数据等)
//    loadModuleWithParams(); //加载水文模型及模型参数，或者模型和参数分开加载
    return true;
}

void pnohs::onStart() {
    mSimulation->simulate();
}

void pnohs::onFinish() {
    // todo remove nodes here (release memory).
    // todo delete simulation context.
    std::cout << "on finish" << std::endl;
}

void pnohs::beforeDestroy() {
    // todo delete simulation
    // todo delete config
    std::cout << "before destroy" << std::endl;
}

// do not use mpi in onDestroy.
void pnohs::onDestroy() {
    std::cout << "on destroy" << std::endl;
};