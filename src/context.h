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

    /**
     * select method pick one node that can run (this node didn't finish simulation, and its all upstream is ready).
     * todo thread block in select.
     * @return true for no more available node
     */
    bool select();

    /**
     * add a simulation node to vector @var simulationNodes,
     */
    void addSimulationNode(const SimulationNode &snode);

    /**
     *  abort all processors with exit code specified by {@var code}
     * @param reason the error message wil print.
     * @param code exit code
     */
    void abort(const std::string &reason, int code);

private:
    ConfigToml *pConfig;
    std::vector<SimulationNode> simulationNodes;
};

#endif //PNOHS_CONTROLLER_H
