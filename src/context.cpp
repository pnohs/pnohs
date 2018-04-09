//
// Created by genshen on 2018-03-28.
//

#include <iostream>
#include <utils/mpi_utils.h>
#include "context.h"
#include "message/looper.h"

Context::Context(ConfigToml *pConfig) : pConfig(pConfig) {}

Context::~Context() { // todo delete context.

}

void Context::abort(const std::string &reason, int code) {
    if (kiwi::mpiUtils::ownRank == MASTER_PROCESSOR) {
        std::cerr << reason << std::endl;
    }
    MPI_Abort(MPI_COMM_WORLD, code);
}
