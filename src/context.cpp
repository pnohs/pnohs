//
// Created by genshen on 2018-03-28.
//

#include <iostream>
#include <utils/mpi_utils.h>
#include "context.h"

Context::Context(ConfigToml *pConfig) : simulationNodes() {
    this->pConfig = pConfig;
}

// todo select strategy.
bool Context::select() {
    for (SimulationNode &sNode : simulationNodes) {
        if (sNode._time_steps <= pConfig->simulationTimeSteps
            && sNode.upstream.isReady()) {
            curNode = &sNode;
            return true;
        }
    }
    return false;
}

void Context::addSimulationNode(const SimulationNode &snode) {
    simulationNodes.push_back(snode);
}

void Context::abort(const std::string &reason, int code) {
    if (kiwi::mpiUtils::ownRank == MASTER_PROCESSOR) {
        std::cerr << reason << std::endl;
    }
    MPI_Abort(MPI_COMM_WORLD, code);
}
