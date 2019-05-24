//
// Created by genshen on 7/2/18.
//

#ifndef PNOHS_MODEL_CONTEXT_H
#define PNOHS_MODEL_CONTEXT_H

#include "utils/predefine.h"

/**
 * Model Context is used in simulation for passing node information (e.g. area of simulation node.)
 * to runoff model and river routing mode.
 * In other words, model context is shared by runoff model and routing mode on the same sub-basin.
 */
class ModelContext {
public:
    double area; // todo example property of this node.
    double flow;

    ModelContext();

    virtual ~ModelContext();

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
