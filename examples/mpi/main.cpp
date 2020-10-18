//
// Created by genshen on 2020/6/17.
//

#include <mpi.h>
#include <nodes_pool.h>
#include <utils/sim_domain.h>
#include <adapter/model_register.h>
#include <scheduler/strategy_container.h>
#include <scheduler/longest_pickup.h>
#include <scheduler/scheduler.h>
#include <event/message_looper.h>
#include <message/looper.h>
#include <logs/logs.h>
#include "model_mpi.hpp"


#define STEPS 10
#define runoffModelName  "example_runoff_mpi"
#define routingModelName "example_routing_mpi"

// function implementation is in common/set_nodes.cpp
void setupNodes(NodesPool *p_node_pool, MPI_Comm comm);

int main(int argc, char **argv) {
    int provided;
    // initialize MPI with multiple threads support.
    MPI_Init_thread(&argc, &argv, MPI_THREAD_MULTIPLE, &provided);
    if (provided != MPI_THREAD_MULTIPLE) { // todo smaller then?
        kiwi::logs::e("MPI", "mpi thread not supported.\n");
        return 1;
    }

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    if (world_size != 3) {
        printf("You must run this with 3 processes.\n");
        return 1;
    }

    // set mpi domain for simulation
    domain::setCommDomain(MPI_COMM_WORLD);
    kiwi::mpiUtils::onGlobalCommChanged(MPI_COMM_WORLD);

    // set nodes and upstream/downstream relationship for each process
    NodesPool *p_node_pool = new NodesPool();
    setupNodes(p_node_pool, MPI_COMM_WORLD);

    // runoff models
    ModelRegister::registerRunoffModel(runoffModelName, ExampleRunoffModel::newInstance);
    // routing models
    ModelRegister::registerRoutingModel(routingModelName, ExampleRoutingModel::newInstance);
    // bind models for each node
    p_node_pool->forEachNode([](SimulationNode &snode) -> bool {
        snode.setModelContext(new ExampleContext(snode.id));

        RunoffAdapter *runoffModel = ModelRegister::newInstanceRunoff(
                ModelRegister::getModelIdByKey(runoffModelName));
        RoutingAdapter *routingModel = ModelRegister::newInstanceRouting(
                ModelRegister::getModelIdByKey(routingModelName));

        if (runoffModel == nullptr || routingModel == nullptr) {
            kiwi::logs::e("loadModel", "create runoff or routing model error!\n");
        }
        snode.setModels(runoffModel, routingModel);
        return false;
    });

    // set scheduler strategy
    SContext *schCtx = new SContext(p_node_pool, STEPS);
    SysContext *sysCtx = new SysContext();
    Scheduler *scheduler = new Scheduler(*sysCtx, *schCtx);
    StrategyContainer::registerStrategy(LongestPickup::Key, new LongestPickup(*schCtx));
    scheduler->setPickupStrategy(LongestPickup::Key);

    // start message loop
    kiwi::MessageLooper::registerRunner(
            new StreamRoutingMessageRunner(*sysCtx, schCtx->pNodesPool, STEPS));
    // New message loop for listening message from other processes.
    // message listener domain must be set before starting this looper.
    Looper *loop = Looper::NewMessageLooper(); // todo delete
    if (loop == nullptr) {
        sysCtx->abort("Error: pthread_create() failed.", 1);
    }

    // run simulation
    while (scheduler->select()) {
        schCtx->curNode->beforeStep();
        schCtx->curNode->runoff();
        schCtx->curNode->routing();
        if (schCtx->curNode->_time_step + 1 == STEPS) { // only print flow of each node at the last step
            kiwi::logs::v("flow", "flow of node {} at step {} is {}\n",
                          schCtx->curNode->id, STEPS, schCtx->curNode->_p_model_ctx->flow);
        }
        // deliver simulation results.
        schCtx->pNodesPool->deliver(*(schCtx->curNode));
        schCtx->curNode->postStep();
        scheduler->postStep(); // update simulation variable after finishing a step of simulation.
    }

    MPI_Finalize();
    return 0;
}
