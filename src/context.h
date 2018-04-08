//
// Created by genshen on 3/28/18.
//

#ifndef PNOHS_CONTROLLER_H
#define PNOHS_CONTROLLER_H

#include "simulation_node.h"
#include "config_toml.h"
#include "nodes_pool.h"

class Context {
public:
    SimulationNode *curNode = nullptr;

    // it is not empty at runtime.
    NodesPool *nodesPool; // all nodes

    Context(ConfigToml *pConfig);

    ~ Context();

    /**
     * New message loop for listening message from other processors.
     */
    void newMessageLoop();

    /**
     * select method pick one node that can run (this node didn't finish simulation, and its all upstream is ready).
     * If there is no node available, the thread will get blocked, until there is at least one node available.
     * @return true for no more available node
     */
    bool select();

    /**
     *  abort all processors with exit code specified by {@var code}
     * @param reason the error message wil print.
     * @param code exit code
     */
    void abort(const std::string &reason, int code);

private:
    ConfigToml *pConfig;

    // pthread variable
    int _t_waiting = 0;
    pthread_mutex_t _t_mu;
    pthread_cond_t _t_cond;

};

#endif //PNOHS_CONTROLLER_H
