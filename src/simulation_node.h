//
// Created by genshen on 3/27/18.
//

#ifndef PNOHS_SIMULATION_NODE_H
#define PNOHS_SIMULATION_NODE_H

#include "graph/node.h"

class SimulationNode : public Node {

private:
    // time steps of this node.
    unsigned long _time_steps;
};


#endif //PNOHS_SIMULATION_NODE_H
