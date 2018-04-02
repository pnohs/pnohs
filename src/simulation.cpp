//
// Created by genshen on 2018-03-27.
//

#include <utils/mpi_utils.h>
#include <iostream>
#include "simulation.h"
#include "dispatch/dispatch_parse.h"


Simulation::Simulation() {
    pConfig = ConfigToml::newInstance();
    ctx = new Context(pConfig); // todo delete
}

void Simulation::setupNodes() {
    // parse dispatch file to get nodes for this processor.
    std::string dispatchFilePath = this->pConfig->dispatchFilePath;
    std::fstream fs = std::fstream(dispatchFilePath, std::ios::in | std::ios::binary);
    if (!fs.good()) {
        ctx->abort("file" + dispatchFilePath + "not exit", 1);
    }

    DispatchParse pa = DispatchParse(fs, kiwi::mpiUtils::ownRank);
    pa.locate();

    DNode node;
    while (pa.isAfterLast()) {
        node = pa.nextNode();
//        ctx
    }
    fs.close();

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
