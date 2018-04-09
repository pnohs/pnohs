//
// Created by genshen on 4/9/18.
//

#include "scheduler.h"

Scheduler::Scheduler(Context &ctx, unsigned long total_steps) : ctx(ctx), _total_steps() {}

Scheduler::~Scheduler() {
    // delete nodesPool; // todo remove all nodes.
}

bool Scheduler::select() {
    if (allFinished()) { // all simulation nodes have finished their simulation.
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
    for (SimulationNode &sNode : nodesPool->simulationNodes) {
        if (sNode._time_steps <= _total_steps && sNode.upstream.isReady()) {
            return &sNode;
        }
    }
    return nullptr;
}

bool Scheduler::allFinished() {
    for (SimulationNode &sNode : nodesPool->simulationNodes) {
        if (sNode._time_steps <= _total_steps) {
            return false;
        }
    }
    return true;
}
