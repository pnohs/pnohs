//
// Created by genshen on 2020/7/2.
//
// This example show a demo, which can be used by calibration program.
// In this demo, the global MPI ranks in MPI_COMM_WORLD are divided into
// several groups (called simulation domain).
// Ranks in each simulation domain can perform a complete hydrological
// simulation using given runoff model and routing model.
// In each simulation domain, the hydrological simulation can be run several
// times (iteration loop) with different model parameters.
//

#include <array>
#include <vector>

#include <mpi.h>
#include <nodes_pool.h>
#include <utils/sim_domain.h>
#include <adapter/model_register.h>
#include <logs/logs.h>
#include <scheduler/s_context.h>
#include <scheduler/scheduler.h>
#include <scheduler/longest_pickup.h>
#include <scheduler/strategy_container.h>
#include <event/message_looper.h>
#include "model_multi_domain.hpp"
#include "joinable_message_looper.h"

#define ITERATION 4
#define STEPS 50
#define PROS_PER_GROUP 3
#define runoffModelName  "example_runoff_multi_domain"
#define routingModelName "example_routing_multi_domain"


// function implementation is in common/set_nodes.cpp
void setupNodes(NodesPool *p_node_pool, MPI_Comm comm);

void bind_models(NodesPool *p_node_pool) {
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
}

// prepared parameter for each nodes in current process.
std::vector<param_const> PARAM_FOR_A_NODE;

const std::vector<param_const *> loadParams(int itl, int rank_in_group) {
    param_const rescale_param = {};
    switch (itl) {
        case 0:
            rescale_param.float_param = 1.0;
            break;
        case 1:
            rescale_param.float_param = 10.0;
            break;
        case 2:
            rescale_param.float_param = 100.0;
            break;
        case 3:
            rescale_param.float_param = 1000.0;
            break;
        default:
            rescale_param.float_param = -1.0;
    }
    PARAM_FOR_A_NODE = {rescale_param, rescale_param};
    // in this example, 6 is the max node number for a MPI process.
    return std::vector<param_const *>{
            PARAM_FOR_A_NODE.data(), PARAM_FOR_A_NODE.data(),
            PARAM_FOR_A_NODE.data(), PARAM_FOR_A_NODE.data(),
            PARAM_FOR_A_NODE.data(), PARAM_FOR_A_NODE.data(),
    };
}

int main(int argc, char **argv) {
    int provided;
    // initialize MPI with multiple threads support.
    MPI_Init_thread(&argc, &argv, MPI_THREAD_MULTIPLE, &provided);
    if (provided != MPI_THREAD_MULTIPLE) { // todo smaller then?
        kiwi::logs::e("MPI", "mpi thread not supported.\n");
        return 1;
    }

    int world_rank, world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    if (world_size % PROS_PER_GROUP != 0) {
        printf("You must run this with %dn processes (where n is number of simulation domains).\n", PROS_PER_GROUP);
        return 1;
    }

    // split the global domain into ${GROUPS} groups.
    // Each groups has 3 processes
    int color = world_rank / PROS_PER_GROUP;
    // Split the communicator based on the color.
    MPI_Comm row_comm;
    MPI_Comm_split(MPI_COMM_WORLD, color, world_rank, &row_comm);

    // set mpi domain for simulation
    domain::setCommDomain(row_comm);

    // set nodes and upstream/downstream relationship for each process
    NodesPool *p_node_pool = new NodesPool();
    setupNodes(p_node_pool, domain::mpi_sim_process.comm);

    // bind routing and runoff modes for each model in mpi processes
    bind_models(p_node_pool);

    // set scheduler strategy
    SContext *schCtx = new SContext(p_node_pool, STEPS);
    SysContext *sysCtx = new SysContext();
    Scheduler *scheduler = new Scheduler(*sysCtx, *schCtx);
    StrategyContainer::registerStrategy(LongestPickup::Key, new LongestPickup(*schCtx));
    scheduler->setPickupStrategy(LongestPickup::Key);

    // gather ids
    Graph graph;
    p_node_pool->toPureGraph(&graph);
    std::vector<_type_node_id> ids = graph.getLocalGraphNodesIds();

    for (int i = 0; i < ITERATION; i++) {
        if (world_rank == 0) {
            kiwi::logs::v("iteration", "running iteration: {}.\n", i + 1);
        }
        // start message loop
        kiwi::MessageLooper::registerRunner(
                new StreamRoutingMessageRunner(*sysCtx, schCtx->pNodesPool, STEPS));
        // New message loop for listening message from other processes.
        // message listener domain must be set before starting this looper.
        JoinableMessageLooper *loop = JoinableMessageLooper::NewMessageLooper();
        if (loop == nullptr) {
            sysCtx->abort("Error: pthread_create() failed.", 1);
        }

        // set parameter for nodes of current local MPI process
        p_node_pool->setNodesParams(ids, loadParams(i, domain::mpi_sim_process.own_rank),
                                    loadParams(i, domain::mpi_sim_process.own_rank));
        // run completed simulation
        while (scheduler->select()) {
            schCtx->curNode->beforeStep();
            schCtx->curNode->runoff();
            schCtx->curNode->routing();
            // only print flow of outlet node at the last step
            if (schCtx->curNode->_time_step + 1 == STEPS && schCtx->curNode->isRiverOutlet()) {
                kiwi::logs::v("flow", "flow of node {} at step {} is {}\n",
                              schCtx->curNode->id, STEPS, schCtx->curNode->_p_model_ctx->flow);
            }
            // deliver simulation results.
            schCtx->pNodesPool->deliver(*(schCtx->curNode));
            schCtx->curNode->postStep();
            scheduler->postStep(); // update simulation variable after finishing a step of simulation.
        }

        loop->Wait(); // wait message thread to finish.
        delete loop; // release loop memory

        MPI_Barrier(row_comm); // fixme: remove mpi barrier
        // reset
        schCtx->reset(); // reset scheduler context (including resetting nodes poll).
        // reset nodes variables and time step
        schCtx->pNodesPool->forEachNode(
                [](SimulationNode &snode) -> bool {
                    snode.reset();
                    return false;
                });
    }

    MPI_Finalize();
    return 0;
}
