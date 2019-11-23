//
// Created by genshen on 7/2/18.
//

#ifndef PNOHS_MODEL_CONTEXT_H
#define PNOHS_MODEL_CONTEXT_H

#include "utils/predefine.h"
#include "type_routing.h"

/**
 * Model Context is used in simulation for passing node information (e.g. area of simulation node.)
 * to runoff model and river routing mode.
 * In other words, model context is shared by runoff model and routing mode on the same sub-basin.
 */
class ModelContext {
public:
    double area; // todo example property of this node.

    // flow at outlet of the sub-basin at current step
    double flow;

    ModelContext();

    virtual ~ModelContext();

    /**
     * function be called before each simulation step.
     * Which also be executed before running run-off and routing models of each time step.
     * e.g. reset flows for current step in this function.
     */
    virtual void beforeStep();

    /**
     * When the run-off and routing model are executed on sub-basin,
     * the results should be passed to its downstream sub-basin.
     * In this function, the data passed to sub-basin will be append to parameter \param flows.
     * \param flows the flows to be passed to downstream (set here)
     */
    virtual void flowsToDownstream(TypeRouting::tp_routing_data *flows);

    /**
     * When the model context is bind to a simulation node,
     * this interface will be called.
     * @param node_id
     */
    virtual void onBind(const _type_node_id node_id) = 0;

    /**
     * for multiple simulation, the model context can be recyclable.
     * if the model context recyclable, the instance of current ModelContext will be used in next simulation,
     * and @memberof onRecycle will be called to reset this context for next simulation;
     * otherwise a new the instance of ModelContext will be created to perform next simulation.
     * @return true for recyclable, false for not recyclable.
     */
    virtual bool isRecyclable() = 0;

    /**
     * reset this context for performing next simulation, or create a new context.
     * @return current ModelContext(for recyclable) or new a ModelContext (for non-recyclable).
     */
    virtual ModelContext *onRecycle(bool recyclable) = 0;
};


#endif //PNOHS_MODEL_CONTEXT_H
