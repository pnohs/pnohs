//
// Created by genshen on 2018-03-28.
//

#include <iostream>
#include <utils/mpi_utils.h>
#include "context.h"

Context::Context(ConfigToml *pConfig) : pConfig(pConfig), curNode(nullptr) {
    nodesPool = new NodesPool(pConfig->simulationTimeSteps);
}

Context::~Context() {
    delete nodesPool; // todo remove all nodes.
}

bool Context::select() {
    if (nodesPool->allFinished()) { // all simulation nodes have finished their simulation.
        return false;
    }

    // select one node can be simulated.
    SimulationNode *pickedNode = nullptr;
    while (1) {
        pickedNode = nodesPool->pickRunnable();
        if (pickedNode != nullptr) {
            curNode = pickedNode;
            return true;
        } else {
            // todo block thread, waiting for result.
            continue;
        }
    }
}

void Context::abort(const std::string &reason, int code) {
    if (kiwi::mpiUtils::ownRank == MASTER_PROCESSOR) {
        std::cerr << reason << std::endl;
    }
    MPI_Abort(MPI_COMM_WORLD, code);
}
