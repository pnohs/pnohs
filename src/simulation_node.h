//
// Created by genshen on 3/27/18.
//

#ifndef PNOHS_SIMULATION_NODE_H
#define PNOHS_SIMULATION_NODE_H

#include "graph/node.h"

class SimulationNode : public Node {

public:
    // time steps of this node.
    // if the total steps is 100, then the valid @var _time_step will be 0,1,...,99.
    unsigned long _time_steps = 0; // zero as initial value.

    void runoff();

    void riverRouting();

private:

};


#endif //PNOHS_SIMULATION_NODE_H
