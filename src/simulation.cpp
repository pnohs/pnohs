//
// Created by genshen on 2018-03-27.
//

#include <utils/mpi_utils.h>
#include <iostream>
#include <event/message_looper.h>
#include "simulation.h"
#include "dispatch/dispatch_parse.h"
#include "message/looper.h"
#include "message/stream_routing_message_runner.h"

Simulation::Simulation() {
    pConfig = ConfigToml::getInstance();
    ctx = new Context(pConfig); // todo release memory
    scheduler = new Scheduler(*ctx, pConfig->simulationTimeSteps); // todo delete.
}

void Simulation::setupNodes() {
    std::string dispatchFilePath = this->pConfig->dispatchFilePath;
    std::fstream fs(dispatchFilePath, std::ios::in | std::ios::binary);
    if (!fs.good()) { // file not exist, exit.
        ctx->abort("[Error] open file " + dispatchFilePath + " error.", 1);
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
        snode.notifyDataSetChanged();
        // add more information to SimulationNode.
        scheduler->pNodesPool->appendNode(snode);
    }
    fs.close();
}

void Simulation::startMessageLooper() {
    kiwi::MessageLooper::registerRunner(
            new StreamRoutingMessageRunner(*ctx, scheduler->pNodesPool, pConfig->simulationTimeSteps));
    // New message loop for listening message from other processors.
    Looper *loop = Looper::NewMessageLooper(); // todo delete
    if (loop == nullptr) {
        ctx->abort("Error: pthread_create() failed.", 1);
    }
}

void Simulation::simulate() {
    while (scheduler->select()) {
        scheduler->curNode->riverRouting();
        scheduler->curNode->runoff();
        // deliver simulation results.
        scheduler->pNodesPool->deliver(scheduler->curNode);
        scheduler->postStep(); // update simulation variable after finishing a step of simulation.
        // todo write results of this time-step of this node to I/O.
    }
    // To here, it has finished all simulation time steps.
}
