//
// Created by genshen on 2017/12/24.
//

#include <utils/mpi_utils.h>
#include <args.hpp>
#include "pnohs.h"
#include "iostream"

bool pnohs::beforeCreate(int argc, char *argv[]) {
    // parse arguments using lib args: https://github.com/Taywee/args.
    args::ArgumentParser parser("pnohs: A Hydrological Simulation framework.",
                                "Copyright (C) 2017-2018 USTB.");
    args::HelpFlag help(parser, "help", "Display this help menu.", {'h', "help"});
    args::Flag version(parser, "version", "Display version flag.", {'v', "version"});
    args::ValueFlag<std::string> configPath(parser, "filepath", "The path of config file.", {'c', "conf"});

    try {
        parser.ParseCLI(argc, argv);
    }
    catch (args::Help) {
        std::cout << parser;
        return false;
    }
    catch (args::ParseError e) {
        std::cerr << e.what() << std::endl;
        std::cerr << parser;
        return false;
    }
    catch (args::ValidationError e) {
        std::cerr << e.what() << std::endl;
        std::cerr << parser;
        return false;
    }

    // version
    if (version) {
        std::cerr << "version 0.1.0" << std::endl
                  << "Copyright (C) 2017-2018 USTB" << std::endl;
        return false;
    }

    if (configPath) {
        configFilePath = args::get(configPath);
        return true;
    }

    // if no args, print usage.
    std::cerr << parser;
    return false;
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
        pConfig = ConfigToml::getInstance();
    }
    pConfig->sync(); // sync config data to other processors from master processor.

}

bool pnohs::prepare() {
    // new simulation instance.
    mSimulation = new Simulation(); // todo delete
    // initial river nodes and their upstream/downstream (up/down stream nodes ids and MPI rank id).
    mSimulation->setupNodes();
//  todo  loadData(nodes);     // 根据结点加载模拟需要的数据(如地理信息数据、河段数据等)
//  todo  loadModuleWithParams(); //加载水文模型及模型参数，或者模型和参数分开加载
    mSimulation->startMessageLooper(); // start mpi message (e.g. upstream simulation result) listening
    return true;
}

void pnohs::onStart() {
    mSimulation->simulate();
}

void pnohs::onFinish() {
    // todo remove nodes here (release memory).
    // todo delete simulation context.
    std::cout << "on finish of " << kiwi::mpiUtils::ownRank << std::endl;
}

void pnohs::beforeDestroy() {
    // todo delete simulation
    // todo delete config
    if (kiwi::mpiUtils::ownRank == MASTER_PROCESSOR) {
        std::cout << "before destroy" << std::endl;
    }
}

// do not use mpi in onDestroy.
void pnohs::onDestroy() {
    if (kiwi::mpiUtils::ownRank == MASTER_PROCESSOR) {
        std::cout << "on destroy" << std::endl;
    }
};