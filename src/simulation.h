//
// Created by genshen on 3/27/18.
//

#ifndef PNOHS_SIMULATION_H
#define PNOHS_SIMULATION_H


#include "config_toml.h"
#include "simulation_node.h"
#include "sys_context.h"
#include "scheduler/scheduler.h"

class Simulation {
public:
    Simulation();

    // get required simulation units (the nodes subset in river-routing relationship graph)
    // allocated to this processor according to mipRankId
    // by reading from dispatch result files.
    void setupNodes();

    /**
     * start real simulation. simulate all nodes, simulate all time-steps.
     */
    void simulate();

    /**
     * start message listen.
     * e.g. upstream simulation result message from other processor through mpi communication.
     */
    void startMessageLooper();

    /**
     * clean simulation after finished all simulation time-steps.
     */
    void teardown();

private:
    ConfigValues *pConfig; // config values pointer.
    SysContext *sysCtx; // system context
    SContext *schCtx; // schedule context
    Scheduler *scheduler;
};


#endif //PNOHS_SIMULATION_H
