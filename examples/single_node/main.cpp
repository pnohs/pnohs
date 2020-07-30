//
// Created by genshen on 2020/6/12.
//
// This file is a implementation of single node with runoff and routing model.
//

#include <iostream>
#include <mpi.h>
#include <logs/logs.h>
#include "adapter/model_register.h"
#include "simulation_node.h"
#include "model.hpp"

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    // create simulation node (only single node here)
    const unsigned long node_id = 0x001;
    SimulationNode snode(node_id);

    // create and set context for this node
    ExampleContext *modelContext = new ExampleContext(snode.id);
    snode.setModelContext(modelContext);

    const std::string runoffModelName = "example_runoff";
    const std::string routingModelName = "example_routing";
    // runoff models
    ModelRegister::registerRunoffModel(runoffModelName,
                                       ExampleRunoffModel::newInstance);
    // routing models
    ModelRegister::registerRoutingModel(routingModelName,
                                        ExampleRoutingModel::newInstance);

    // create runoff model for this node
    const _type_model_id runoff_model_id = ModelRegister::getModelIdByKey(runoffModelName);
    RunoffAdapter *runoffAdapter = ModelRegister::newInstanceRunoff(runoff_model_id);
    if (runoffAdapter == nullptr) {
        kiwi::logs::e("loadModel", "runoff model {0} is not supported!\n", runoffModelName);
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    // create routing model for this node
    const _type_model_id routing_model_id = ModelRegister::getModelIdByKey(routingModelName);
    RoutingAdapter *routingAdapter = ModelRegister::newInstanceRouting(routing_model_id);
    if (routingAdapter == nullptr) {
        kiwi::logs::e("loadModel", "routing model {0} is not supported!\n", routingModelName);
        MPI_Abort(MPI_COMM_WORLD, 1);
    }
    // set runoff mode and routing mode
    snode.setModels(runoffAdapter, routingAdapter);

    // now, run the runoff mode and routing mode on the node
    for (unsigned long i = 0; i < 40; i++) {
        snode.beforeStep(); // call context.beforeStep
        snode.runoff(); // call runoff model
        snode.routing();  // call routing model
        // deliver simulation results if there it is in parallel env
        std::cout << "flow at step " << i + 1 << " is: " << snode._p_model_ctx->flow << std::endl;
        snode.postStep(); // plus 1 to time step of current node.
    }

    MPI_Finalize();
    return 0;
}
