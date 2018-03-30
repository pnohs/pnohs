//
// Created by genshen on 3/27/18.
//

#include <utils/mpi_utils.h>
#include "simulation.h"
#include "partition/partition_parse.h"


Simulation::Simulation() {
    pConfig = ConfigToml::newInstance();
    ctx = new Context(pConfig);
}

void Simulation::setupNodes() {
    PartitionParse *pa = new PartitionParse(this->pConfig->partitionFilePath, kiwi::mpiUtils::ownRank);
    pa->locate();
    while (pa->nextNode()) {

    }
    // todo parse partition file.
    ctx->newTaskQueue();
}

void Simulation::simulate() {
    while (ctx->select()) {
        ctx->curNode->riverRouting();
        ctx->curNode->runoff();
        ctx->curNode->deliver();
        // todo write results of this time-step of this node to I/O.
    }
    // To here, it has finished all simulation time steps.
}
