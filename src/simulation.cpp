//
// Created by genshen on 2018-03-27.
//

#include <utils/mpi_utils.h>
#include <event/message_looper.h>
#include <logs/logs.h>
#include "simulation.h"
#include "dispatch/dispatch_parse.h"
#include "message/looper.h"
#include "message/stream_routing_message_runner.h"
#include "scheduler/strategy_container.h"
#include "scheduler/ring_pickup.h"
#include "scheduler/simple_pickup.h"

Simulation::Simulation() {
    pConfig = ConfigToml::getInstance()->getConfigValue();
    sysCtx = new SysContext();
    schCtx = new SContext(pConfig->simulationTimeSteps); // todo delete
    scheduler = new Scheduler(*sysCtx, *schCtx);
}

void Simulation::setupNodes() {
    std::string dispatchFilePath = this->pConfig->dispatchFilePath;
    std::fstream fs(dispatchFilePath, std::ios::in | std::ios::binary);
    if (!fs.good()) { // file not exist, exit.
        sysCtx->abort("open file " + dispatchFilePath + " error.", 1);
    }

    // parse dispatch file to get nodes for this processor.
    DispatchParse pa = DispatchParse(fs, kiwi::mpiUtils::ownRank);
    pa.locate();

    // todo too many object copies, but maybe it is not too important.
    DNode dnode;
    while (pa.isAfterLast()) { // add nodes to vector onr by one.
        dnode = pa.nextNode();
        SimulationNode snode;
        snode.id = dnode.node_id;

        for (const StreamMeta &meta:dnode.getUpstreamNodes()) {
            snode.upstream.putUpMetaStream(meta); // add upstream node and with its task queue.
        }
        for (const StreamMeta &meta:dnode.getDownstreamNodes()) {
            snode.downstream.putDownMetaStream(meta); // add downstream node.
        }
        snode.testInit();
        snode.notifyDataSetChanged();
        // add more information to SimulationNode.
        schCtx->pNodesPool->appendNode(snode);
    }
    fs.close();
}

void Simulation::startMessageLooper() {
    kiwi::MessageLooper::registerRunner(
            new StreamRoutingMessageRunner(*sysCtx, schCtx->pNodesPool, pConfig->simulationTimeSteps));
    // New message loop for listening message from other processors.
    Looper *loop = Looper::NewMessageLooper(); // todo delete
    if (loop == nullptr) {
        sysCtx->abort("Error: pthread_create() failed.", 1);
    }
}

void Simulation::simulate() {
    std::string pickupStrategyName = pConfig->pickupStrategy;

    // register all kinds od strategy here.
    StrategyContainer::registerStrategy(SimplePickup::Key, new SimplePickup(*schCtx));
    StrategyContainer::registerStrategy(RingPickup::Key, new RingPickup(*schCtx));
    if (StrategyContainer::findStrategyByKey(pickupStrategyName) != nullptr) {
        scheduler->setPickupStrategy(pickupStrategyName);
        kiwi::logs::i("scheduler", "the {} pickup strategy in scheduler will be used.\n", pickupStrategyName);
    } else {
        kiwi::logs::w("scheduler", "invalid strategy name: {0}, "
                                   "we will use default pickup strategy 'ring pickup' instead.\n",
                      pickupStrategyName);
        scheduler->setPickupStrategy(RingPickup::Key);
    }

    while (scheduler->select()) {
        schCtx->curNode->beforeStep();
        schCtx->curNode->routing();
        schCtx->curNode->runoff();
        // deliver simulation results.
        schCtx->pNodesPool->deliver(*(schCtx->curNode)); // todo use current node?
        schCtx->curNode->postStep();
        scheduler->postStep(); // update simulation variable after finishing a step of simulation.
        // todo write results of this time-step of this node to I/O.
    }
    // To here, it has finished all simulation time steps.
}

void Simulation::teardown() {
    // destroy all pickup strategies.
    StrategyContainer::DestroyAllStrategies();
    delete sysCtx; // delete simulation context
    delete scheduler; // remove simulation nodes here
}
