//
// Created by genshen on 3/27/18.
//

#include <logs/logs.h>
#include "simulation_node.h"

void SimulationNode::routing() {
    // Dequeue upstreams // write queue
    // the task queue must have data (because this node is the pickup/runnable node).
    // and the other thread only add data to task queue (don't remove data).
    if (!isRiverOrigin()) {
        std::list<TypeRouting> routing_data = upstream.deQueue();
        _p_routing_model->stashUpstreamRouting(routing_data);
        _p_routing_model->exec(_p_model_ctx);
    }
}

void SimulationNode::runoff() {
    _p_runoff_model->exec(_p_model_ctx);
}

void SimulationNode::outletReached() const {
    kiwi::logs::i("flow", "flow is: {0}\n",
                  _p_model_ctx->flow); // todo for an example, we just output the flow of outlet.
}

TypeRouting SimulationNode::constructRouting() const {
    TypeRouting data = TypeRouting(); // todo just example
    data.routing_data = _p_model_ctx->flow;
    data.source_id = id;
    data.destination_id = downstream.nodes[0].id;
    return data;
}

void SimulationNode::beforeStep() {
    // todo just example.
    // reset flow for current step.
    _p_model_ctx->flow = 0;
}

void SimulationNode::postStep() {
    _time_steps++;
}

void SimulationNode::testInit() {
    _p_model_ctx = new ModelContext();
    _p_routing_model = new RoutingAdapter();
    _p_runoff_model = new RunoffAdapter();
}
