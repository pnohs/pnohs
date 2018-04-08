//
// Created by genshen on 2018-03-28.
//

#include <iostream>
#include <utils/mpi_utils.h>
#include "context.h"
#include "message/looper.h"

Context::Context(ConfigToml *pConfig) : pConfig(pConfig), curNode(nullptr) {
    nodesPool = new NodesPool(pConfig->simulationTimeSteps);
}

Context::~Context() {
    delete nodesPool; // todo remove all nodes.
}

void Context::newMessageLoop() {
    Looper *loop = Looper::NewMessageLooper(); // todo delete
    if (loop == nullptr) {
        abort("Error: pthread_create() failed.", 1);
    }
}

bool Context::select() {
    if (nodesPool->allFinished()) { // all simulation nodes have finished their simulation.
        return false;
    }

    // select one node can be simulated.
    SimulationNode *pickedNode = nullptr;
    while (1) {
        pthread_mutex_lock(&_t_mu); // lock
        pickedNode = nodesPool->pickRunnable(); // read queue
        if (pickedNode == nullptr) {
            _t_waiting++;
            pthread_cond_wait(&_t_cond, &_t_mu);
            _t_waiting--;
            pthread_mutex_unlock(&_t_mu); // lock
            continue;
        } else {
            curNode = pickedNode;
            // todo Dequeue upstreams // write queue
            pthread_mutex_unlock(&_t_mu); // lock
            return true;
        }
    }
}

void Context::abort(const std::string &reason, int code) {
    if (kiwi::mpiUtils::ownRank == MASTER_PROCESSOR) {
        std::cerr << reason << std::endl;
    }
    MPI_Abort(MPI_COMM_WORLD, code);
}
