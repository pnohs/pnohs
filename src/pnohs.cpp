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
    ConfigToml *pConfig;
    if (kiwi::mpiUtils::ownRank == MASTER_PROCESSOR) {
        std::cout << "mpi env was initialed." << std::endl;
        // initial config Obj, then read and resolve config file.
        pConfig = ConfigToml::newInstance(
                "/home/genshen/Documents/workspace/CPlusPlus/hpc/pnohs/example/config.toml"); // todo config file from argv.
        if (pConfig->hasError) {
            std::cerr << "[Error] " << pConfig->errorMessage << std::endl;
            this->abort(2);
        }
    } else {
        // just initial a empty config Obj.
        pConfig = ConfigToml::newInstance();
    }
    pConfig->sync(); // sync config data to other processors from master processor.

    // new simulation instance.
    simulation = new Simulation();
}

bool pnohs::prepare() {
    std::cout << "prepare" << std::endl;

    // get required simulation units (the nodes subset in river-routing relationship graph)
    // allocated to this processor according to mipRankId
    // by reading from partition result files.
//    nodes = readNodesFromFile(rankId);
//    initialNodes(nodes); // 初始化各结点，及其上下游关系(记录各结点的上下游都是哪些结点)
//    loadData(nodes);     // 根据结点加载模拟需要的数据(如地理信息数据、河段数据等)
//    loadModleWithParams(); //加载水文模型及模型参数，或者模型和参数分开加载
//    newTaskQueue(nodes);
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