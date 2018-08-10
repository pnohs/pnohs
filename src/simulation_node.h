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
     * model context for passing data between runoff model and routing model.
     */
    ModelContext *_p_model_ctx;

    RoutingAdapter *_p_routing_model; // todo free mem after new pointer.
    RunoffAdapter *_p_runoff_model;

    /**
     * set river routing model, and initialize this model.
     * @param p_adapter
     */
    void setModelRouting(RoutingAdapter *p_adapter);

    /**
     * set runoff model and initialize this model (by calling onBind(node_id)).
     * @param p_adapter
     */
    void setModelRunoff(RunoffAdapter *p_adapter);

    /**
     * set both runoff model and river routing model.
     * @param p_runoff_adapter runoff model
     * @param p_routing_adapter routing model
     */
    void setModels(RunoffAdapter *p_runoff_adapter, RoutingAdapter *p_routing_adapter);

    /**
     * set mode context for saving model variables.
     * model context must be set before model set, or null context will be passed to initialize model.
     * @param p_context model context.
     */
    void setModelContext(ModelContext *p_context);

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

};


#endif //PNOHS_SIMULATION_NODE_H
