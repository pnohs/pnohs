//
// Created by genshen on 3/27/18.
//

#ifndef PNOHS_SIMULATION_NODE_H
#define PNOHS_SIMULATION_NODE_H

#include "graph/node.h"
#include "adapter/type_routing.h"
#include "adapter/model_context.h"
#include "adapter/runoff_adapter.h"
#include "adapter/routing_adapter.h"

class SimulationNode : public Node {

public:
    /** time steps of this node.
     * if the total steps is 100, then the valid @var _time_step will be 0,1,...,99.
     */
    unsigned long _time_steps = 0;

    /**
     * set river routing model.
     */
    void setModelRouting(RoutingAdapter *p_adapter) {
        _p_routing_model = p_adapter;
    }

    inline void setModelRunoff(RunoffAdapter *p_adapter) {
        _p_runoff_model = p_adapter;
    }

    inline void setModels(RunoffAdapter *p_runoff_adapter, RoutingAdapter *p_routing_adapter) {
        setModelRunoff(p_runoff_adapter);
        setModelRouting(p_routing_adapter);
    }

    inline void setModelContext(ModelContext *p_context) {
        _p_model_ctx = p_context;
    }

    /**
     * run river routing model.
     */
    void routing();

    /**
     * run runoff model.
     */
    void runoff();

    /**
     * you can call this method when current node is the node which has no downstream.
     * to process flow data.
     */
    void outletReached() const; // todo refactor.

    /**
     * construct data of {TypeRouting} type to use(e.g. passing routing data to its downstream).
     * @return
     */
    TypeRouting constructRouting() const;

    /**
     * this method should be called before each time step of simulation.
     */
    void beforeStep();

    /**
     * This method should be called after each time step of simulation.
     * The simulation time step of current node will be increased by 1.
     */
    void postStep();

    void testInit(); // todo initialize context and model.

private:
    ModelContext *_p_model_ctx;
    RoutingAdapter *_p_routing_model;
    RunoffAdapter *_p_runoff_model;

};


#endif //PNOHS_SIMULATION_NODE_H
