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
#include "model.hpp"

void setupNodes(NodesPool *p_node_pool) {
    int rank = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    switch (rank) {
        case 0: // mpi rank 0
        {
            SimulationNode node1(1);
            node1.downstream.putDownMetaStream(StreamMeta{4, 0});
            node1.notifyDataSetChanged();
            p_node_pool->appendNode(node1);

            SimulationNode node2(4);
            node2.upstream.putUpMetaStream(StreamMeta{1, 0});
            node2.downstream.putDownMetaStream(StreamMeta{8, 1});
            node2.notifyDataSetChanged();
            p_node_pool->appendNode(node2);

            SimulationNode node3(7);
            node3.downstream.putDownMetaStream(StreamMeta{10, 0});
            node3.notifyDataSetChanged();
            p_node_pool->appendNode(node3);

            SimulationNode node4(10);
            node4.upstream.putUpMetaStream(StreamMeta{7, 0});
            node4.downstream.putDownMetaStream(StreamMeta{13, 0});
            node4.notifyDataSetChanged();
            p_node_pool->appendNode(node4);

            SimulationNode node5(13);
            node5.upstream.putUpMetaStream(StreamMeta{10, 0});
            node5.upstream.putUpMetaStream(StreamMeta{11, 1});
            node5.downstream.putDownMetaStream(StreamMeta{16, 0});
            node5.notifyDataSetChanged();
            p_node_pool->appendNode(node5);

            SimulationNode node6(16);
            node6.upstream.putUpMetaStream(StreamMeta{13, 0});
            node6.upstream.putUpMetaStream(StreamMeta{14, 1});
            node6.upstream.putUpMetaStream(StreamMeta{12, 2});
            node6.upstream.putUpMetaStream(StreamMeta{15, 2});
            node6.notifyDataSetChanged();
            p_node_pool->appendNode(node6);
        }
            break;
        case 1: // mpi rank 1
        {
            SimulationNode node1(2);
            node1.downstream.putDownMetaStream(StreamMeta{8, 1});
            node1.notifyDataSetChanged();
            p_node_pool->appendNode(node1);

            SimulationNode node2(5);
            node2.downstream.putDownMetaStream(StreamMeta{8, 1});
            node2.notifyDataSetChanged();
            p_node_pool->appendNode(node2);

            SimulationNode node3(8);
            node3.upstream.putUpMetaStream(StreamMeta{4, 0});
            node3.upstream.putUpMetaStream(StreamMeta{2, 1});
            node3.upstream.putUpMetaStream(StreamMeta{5, 1});
            node3.upstream.putUpMetaStream(StreamMeta{3, 3});
            node3.downstream.putDownMetaStream(StreamMeta{12, 2});
            node3.notifyDataSetChanged();
            p_node_pool->appendNode(node3);

            SimulationNode node4(11);
            node4.downstream.putDownMetaStream(StreamMeta{13, 0});
            node4.notifyDataSetChanged();
            p_node_pool->appendNode(node4);

            SimulationNode node5(14);
            node5.downstream.putDownMetaStream(StreamMeta{16, 0});
            node5.notifyDataSetChanged();
            p_node_pool->appendNode(node5);
        }
            break;
        case 2: // mpi rank 2
        {
            SimulationNode node1(3);
            node1.downstream.putDownMetaStream(StreamMeta{8, 1});
            node1.notifyDataSetChanged();
            p_node_pool->appendNode(node1);

            SimulationNode node2(6);
            node2.downstream.putDownMetaStream(StreamMeta{9, 2});
            node2.notifyDataSetChanged();
            p_node_pool->appendNode(node2);

            SimulationNode node3(9);
            node3.upstream.putUpMetaStream(StreamMeta{6, 2});
            node3.downstream.putDownMetaStream(StreamMeta{12, 2});
            node3.notifyDataSetChanged();
            p_node_pool->appendNode(node3);

            SimulationNode node4(12);
            node4.upstream.putUpMetaStream(StreamMeta{8, 1});
            node4.upstream.putUpMetaStream(StreamMeta{9, 2});
            node4.downstream.putDownMetaStream(StreamMeta{16, 0});
            node4.notifyDataSetChanged();
            p_node_pool->appendNode(node4);

            SimulationNode node5(15);
            node5.downstream.putDownMetaStream(StreamMeta{16, 0});
            node5.notifyDataSetChanged();
            p_node_pool->appendNode(node5);
        }
            break;
    }
}

#define STEPS 10
#define runoffModelName  "example_runoff_mpi"
#define routingModelName "example_routing_mpi"

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    if (world_size != 3) {
        printf("You must run this with 3 processes.\n");
        return 1;
    }

    // set mpi domain for simulation
    domain::setCommDomain(MPI_COMM_WORLD);

    // set nodes and upstream/downstream relationship for each process
    NodesPool *p_node_pool = new NodesPool();
    setupNodes(p_node_pool);

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
    // New message loop for listening message from other processors.
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
        // deliver simulation results.
        schCtx->pNodesPool->deliver(*(schCtx->curNode));
        schCtx->curNode->postStep();
        scheduler->postStep(); // update simulation variable after finishing a step of simulation.
    }

    MPI_Finalize();
    return 0;
}
