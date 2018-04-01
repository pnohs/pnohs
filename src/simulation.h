//
// Created by genshen on 3/27/18.
//

#ifndef PNOHS_SIMULATION_H
#define PNOHS_SIMULATION_H


#include "config_toml.h"
#include "simulation_node.h"
#include "context.h"

class Simulation {
public:
    Simulation();

    // get required simulation units (the nodes subset in river-routing relationship graph)
    // allocated to this processor according to mipRankId
    // by reading from dispatch result files.
    void setupNodes();

    void simulate();

private:
    ConfigToml *pConfig; // config pointer.
    Context *ctx;

    // deliver simulation result to its downstream.
    void deliver();
};


#endif //PNOHS_SIMULATION_H
