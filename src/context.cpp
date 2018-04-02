//
// Created by genshen on 3/28/18.
//

#include <iostream>
#include <utils/mpi_utils.h>
#include "context.h"

Context::Context(ConfigToml *pConfig) : simulationNodes() {
    this->pConfig = pConfig;
}

void Context::newTaskQueue() {

}

bool Context::select() {
    for (SimulationNode &sNode : simulationNodes) {
        if (sNode._time_steps <= pConfig->simulationTimeSteps
            && sNode.upstream.isReady()) { // todo
            curNode = &sNode;
            return true;
        }
    }
    return false;
}

void Context::abort(const std::string &reason, int code) {
    if (kiwi::mpiUtils::ownRank == MASTER_PROCESSOR) {
        std::cerr << reason << std::endl;
    }
    MPI_Abort(MPI_COMM_WORLD, code);
}
