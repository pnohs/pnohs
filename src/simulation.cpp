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
    std::string dispatchFilePath = this->pConfig->dispatchFilePath;
    std::fstream fs = std::fstream(dispatchFilePath, std::ios::in | std::ios::binary);
    if (!fs.good()) { // file not exist, exit.
        ctx->abort("file" + dispatchFilePath + "not exit", 1);
    }

    // parse dispatch file to get nodes for this processor.
    DispatchParse pa = DispatchParse(fs, kiwi::mpiUtils::ownRank);
    pa.locate();

    // todo too many object copies, but maybe it is not too important.
    DNode dnode;
    while (pa.isAfterLast()) { // add nodes to vector onr by one.
        SimulationNode snode;
        dnode = pa.nextNode();
        snode.id = dnode.node_id;

        for (const StreamMeta &meta:dnode.getUpstreamNodes()) {
            snode.upstream.putUpMetaStream(meta); // add upstream node and with its task queue.
        }
        for (const StreamMeta &meta:dnode.getDownstreamNodes()) {
            snode.downstream.putDownMetaStream(meta); // add downstream node.
        }
        // add more information to SimulationNode.
        ctx->addSimulationNode(snode);
    }
    fs.close();
}

void Simulation::simulate() {
    while (ctx->select()) {
        ctx->curNode->riverRouting();
        ctx->curNode->runoff();
        ctx->curNode->deliver(); // deliver simulation result of this node to its downstream node(s).
        // todo write results of this time-step of this node to I/O.
    }
    // To here, it has finished all simulation time steps.
}
