//
// Created by genshen on 3/27/18.
//

#include "simulation.h"
#include "partition_parse.h"


Simulation::Simulation() {
    pConfig = ConfigToml::newInstance();
    ctx = new Context(pConfig);
}

void Simulation::setupNodes() {
    PartitionParse *parser = new PartitionParse();
    parser->parse(this->pConfig->partitionFilePath);
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
