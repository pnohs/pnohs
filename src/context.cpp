//
// Created by genshen on 2018-03-28.
//

#include <iostream>
#include <utils/mpi_utils.h>
#include "context.h"

Context::Context(ConfigToml *pConfig) : pConfig(pConfig), curNode(nullptr) {
    nodesPool = new NodesPool(pConfig->simulationTimeSteps);
}

bool Context::select() {
    if (nodesPool->allFinished()) { // all simulation nodes have finished their simulation.
        return false;
    }

    SELECT_AGAIN:
    // select one node can be simulated.
    SimulationNode *pickedNodes = nodesPool->pickRunnable();
    if (pickedNodes != nullptr) {
        curNode = pickedNodes;
        return true;
    } else {
        // block thread, waiting for result.
        // todo
        goto SELECT_AGAIN;
    }
}

void Context::abort(const std::string &reason, int code) {
    if (kiwi::mpiUtils::ownRank == MASTER_PROCESSOR) {
        std::cerr << reason << std::endl;
    }
    MPI_Abort(MPI_COMM_WORLD, code);
}
