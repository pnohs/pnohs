//
// Created by genshen on 3/27/18.
//

#include <stdexcept>
#include "simulation_node.h"
#include "utils/predefine.h"

SimulationNode::SimulationNode(const _type_node_id id) : Node(id) {
    // simulation node id shouldn't be null, but graph node id can.
    if (id == NODE_ID_NULL) {
        throw std::invalid_argument("invalid argument id (can not be null) while creating simulation node.");
    }
}

void SimulationNode::setModelRouting(RoutingAdapter *p_adapter) {
    _p_routing_model = p_adapter;
    p_adapter->onBind(_p_model_ctx, id); // bind model to simulation node.
}

void SimulationNode::setModelRunoff(RunoffAdapter *p_adapter) {
    _p_runoff_model = p_adapter;
    p_adapter->onBind(_p_model_ctx, id); // bind model to simulation node.
}

void SimulationNode::setModels(RunoffAdapter *p_runoff_adapter, RoutingAdapter *p_routing_adapter) {
    setModelRunoff(p_runoff_adapter);
    setModelRouting(p_routing_adapter);
}

void SimulationNode::setModelContext(ModelContext *p_context) {
    _p_model_ctx = p_context;
    _p_model_ctx->onBind(id);
}

void SimulationNode::routing() {
    // Dequeue upstreams // write queue
    // the task queue must have data (because this node is the pickup/runnable node).
    // and the other thread only add data to task queue (don't remove data).
    std::list<TypeRouting> routing_data;
    if (!isRiverOrigin()) {
        // todo may large data coping
        routing_data = upstream.deQueue();
    }
    // if the node is river origin, the empty upstream data(std::list<TypeRouting>) will be passed.
    _p_routing_model->stashUpstreamRouting(routing_data);
    _p_routing_model->exec(_p_model_ctx, _time_step);
}

void SimulationNode::runoff() {
    _p_runoff_model->exec(_p_model_ctx, _time_step);
}

void SimulationNode::outletReached() const {
//    kiwi::logs::i("flow", "flow is: {0}\n",
//                  _p_model_ctx->flow); // todo for an example, we just output the flow of outlet.
}

void SimulationNode::constructRoutingData(TypeRouting &routing_data) const {
    // the vector is empty, just a new vector.
    _p_model_ctx->flowsToDownstream(&routing_data.routing_data);
}

void SimulationNode::beforeStep() {
    _p_model_ctx->beforeStep();
}

void SimulationNode::postStep() {
    _time_step++;
}

void SimulationNode::reset() {
    this->_time_step = 0; // reset time step.
    // reset model context
    if (_p_model_ctx->isRecyclable()) {
        _p_model_ctx->onRecycle(true);
    } else {
        ModelContext *temp_ctx = _p_model_ctx;
        _p_model_ctx = _p_model_ctx->onRecycle(false); // create new one
        delete temp_ctx; // remove old one
    }
    // reset runoff model.
    if (_p_runoff_model->isReusable()) {
        _p_runoff_model->onReused(true);
    } else {
        RunoffAdapter *temp_pointer = _p_runoff_model;
        _p_runoff_model = _p_runoff_model->onReused(false);
        delete temp_pointer;
    }
    // reset routing model.
    if (_p_routing_model->isReusable()) {
        _p_routing_model->onReused(true);
    } else {
        RoutingAdapter *temp_pointer = _p_routing_model;
        _p_routing_model = _p_routing_model->onReused(false);
        delete temp_pointer;
    }
}
