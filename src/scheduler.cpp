//
// Created by genshen on 4/9/18.
//

#include <utils/mpi_utils.h>
#include "scheduler.h"

Scheduler::Scheduler(Context &ctx, unsigned long total_steps) : ctx(ctx), _total_steps(total_steps) {
    pNodesPool = new NodesPool();
}

Scheduler::~Scheduler() {
    // delete pNodesPool; // todo remove all nodes.
}

bool Scheduler::select() {
    if (pNodesPool->allCompleted()) { // all simulation nodes have finished their simulation.
        return false;
    }

    // select one node can be simulated.
    SimulationNode *pickedNode = nullptr;
    while (1) {
        pthread_mutex_lock(&(ctx._t_mu)); // lock
        pickedNode = pickRunnable(); // read queue
        if (pickedNode == nullptr) {
            ctx._t_waiting++;
            pthread_cond_wait(&(ctx._t_cond), &(ctx._t_mu));
            ctx._t_waiting--;
            pthread_mutex_unlock(&(ctx._t_mu)); // lock
            continue;
        } else {
            curNode = pickedNode;
            // todo Dequeue upstreams // write queue
            pthread_mutex_unlock(&(ctx._t_mu)); // lock
            return true;
        }
    }
}

// todo milestone: better pick strategy.
SimulationNode *Scheduler::pickRunnable() {
    for (SimulationNode &sNode : pNodesPool->simulationNodes) {
        if (sNode._time_steps < _total_steps && sNode.upstream.isReady()) {
            return &sNode;
        }
    }
    return nullptr;
}

void Scheduler::postStep() {
    curNode->_time_steps++;
    pNodesPool->updateStatus(_total_steps); // update
}
