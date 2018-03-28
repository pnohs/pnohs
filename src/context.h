//
// Created by genshen on 3/28/18.
//

#ifndef PNOHS_CONTROLLER_H
#define PNOHS_CONTROLLER_H


#include "simulation_node.h"
#include "config_toml.h"

class Context {
public:
    SimulationNode *curNode = nullptr;

    Context(ConfigToml *pConfig);

    // initial task queue for every upstream of every node.
    void newTaskQueue();

    // select one node that can run (this node didn't finish simulation, and its all upstream is ready).
    bool select();

private:
    ConfigToml *pConfig;
    std::vector<SimulationNode> simulationNodes;
};

#endif //PNOHS_CONTROLLER_H
