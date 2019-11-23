//
// Created by genshen on 4/4/18.
//

#include <utils/mpi_utils.h>
#include "nodes_pool.h"
#include "utils/sim_domain.h"
#include "adapter/type_routing.h"

NodesPool::NodesPool() {
    simulationNodes = new SimulationNodesSet();
}

NodesPool::~NodesPool() {
    simulationNodes->clear(); // todo release memory.
}

void NodesPool::appendNode(const SimulationNode &snode) { // todo remove all nodes.
    // todo checkout node id not null.
    simulationNodes->push_back(snode);
}

_type_nodes_count NodesPool::nodes() const {
    return simulationNodes->size();
}

SimulationNode *NodesPool::findNodeById(const _type_node_id node_id) {
    // travel all simulation nodes to find a node.
    for (SimulationNode &node:*simulationNodes) {
        if (node.id == node_id) {
            return &node;
        }
    }
    return nullptr;
}

void NodesPool::setNodesParams(const std::vector<_type_node_id> &nodes_ids,
                               const std::vector<param_const *> &runoff_params,
                               const std::vector<param_const *> &routing_params) {
    _type_nodes_count i = 0;
    for (_type_node_id id : nodes_ids) {
        SimulationNode *node = findNodeById(id);
        if (node == nullptr) {
            continue; // todo not exists.
        }
        // todo pass parameters count in this function.
        node->_p_runoff_model->onParamsPassed(node->_p_model_ctx, runoff_params[i],
                                              node->_p_runoff_model->paramCount());
        node->_p_routing_model->onParamsPassed(node->_p_model_ctx, routing_params[i],
                                               node->_p_routing_model->paramCount());
        i++;
    }
}

void NodesPool::toPureGraph(Graph *graph) {
    for (SimulationNode &snode: *simulationNodes) {
        graph->addNode(snode);
    }
}

void NodesPool::deliver(const SimulationNode &current_node) {
    if (current_node.isRiverOutlet()) {
        // if its outlet of this river
        current_node.outletReached();
    } else {
        TypeRouting routing_data(current_node.id, current_node.downstream.nodes[0].id);
        // if its downstream is on this processor, just do data copy in memory.
        if (domain::mpi_sim_process.own_rank == current_node.downstream.nodes[0].location) {
            straightforwardDeliver(current_node, routing_data);
        } else {
            // deliver stream routing data to the downstream node on the remote processor
            // using MPI message sending
            const DownstreamNode &downstream_node = current_node.downstream.nodes[0];
            // set routing data
            current_node.constructRoutingData(routing_data);
            routing_data.routingSend(downstream_node.location, domain::mpi_sim_process.comm);
        }
    }
}

// todo usr event message.
void NodesPool::straightforwardDeliver(const SimulationNode &current_node, TypeRouting &routing_data) {
    _type_node_id downstream_node_id = current_node.downstream.nodes[0].id;
    SimulationNode *downstreamNode = findNodeById(downstream_node_id);
    if (downstreamNode != nullptr) {
        // set routing data
        current_node.constructRoutingData(routing_data);
        // append routing results to upstream task list directly.
        // todo may large data coping
        bool append_status = downstreamNode->upstream.appendUpstreamRouting(current_node.id, routing_data);
        // New task will be append to the task queue, but there is no need to wake up the blocked main thread.
        // because the main thread is running here.
        if (!append_status) {
            // todo log warning.
        } else {
//            updatePotentiallyCompletedStatus(); // todo
        }
    } else {
        // todo fault error, downstream not found on processor xxx.
    }
}

bool NodesPool::allCompleted() {
    return status_all_tasks_completed;
}

// update variable @var status_tasks_potentially_completed and @var status_all_tasks_completed.
void NodesPool::updateStatusAllCompleted(const unsigned long total_steps) {
    bool finish_status = true;
    // update status_all_tasks_completed
    for (SimulationNode &sNode : *simulationNodes) {
        if (sNode._time_step < total_steps) { // the node does not finish its simulation.
            finish_status = false;
            break;
        }
    }
    status_all_tasks_completed = finish_status;
}

void NodesPool::clearStatus() {
    status_all_tasks_completed = false;
}
