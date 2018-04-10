//
// Created by genshen on 2018-03-28.
//

#include <iostream>
#include <utils/mpi_utils.h>
#include "context.h"
#include "message/looper.h"

Context::Context(ConfigToml *pConfig) : pConfig(pConfig) {
    // todo use pthread_once: https://linux.die.net/man/3/pthread_mutex_init
    // todo destroy
    // initialize pthread mutex and cond
    pthread_mutex_init(&_t_mu, nullptr); // or use static initialize.
    pthread_cond_init(&_t_cond, nullptr);
}

Context::~Context() { // todo delete context.

}

void Context::abort(const std::string &reason, int code) {
    if (kiwi::mpiUtils::ownRank == MASTER_PROCESSOR) {
        std::cerr << reason << std::endl;
    }
    MPI_Abort(MPI_COMM_WORLD, code);
}
