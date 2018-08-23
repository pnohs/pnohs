//
// Created by genshen on 7/2/18.
//

#ifndef PNOHS_MODE_ADAPTER_H
#define PNOHS_MODE_ADAPTER_H

#include "model_context.h"
#include "../ds/model_params_def.h"
#include "../graph/node.h"

/**
 * the common methods used in routing model and runoff mode, are declared here.
 */
class ModelAdapter {
public:
    // it is a good practice to declare virtual destructors for base classes in C++.
    // or the behaviour or deleting Derived object is undefined.
    virtual ~ModelAdapter();

    /**
     * this method is called when a model is bind to some simulation node.
     * @param p_model_context model context
     * @param node_id simulation node id.
     */
    virtual void onBind(ModelContext *p_model_context, _type_node_id node_id) = 0; // todo check model context nullptr.

    /**
     * get parameter count of this model
     * @return default value: 0
     */
    static int paramCount();

    /**
     *
     * implement this method to set parameters for models in this method.
     * this method may be called many time for setting different groups of params.
     * you must check @param params length before indexing it.
     * @param p_model_context pointer to model context
     * @param params data of params.
     */
    virtual void onParamsPassed(ModelContext *p_model_context, param_const params[], size_t size) = 0;

    /*
     * run the model.
     */
    virtual void exec(ModelContext *p_context, unsigned long time_steps) = 0;

    /**
     * For multiple simulation, the model context can be reusable.
     * if the model context reusable, the instance of this Model will be used in next simulation,
     * and @memberof onReused will be called to reset the model for next simulation;
     * otherwise a new the instance of this kind of model will be created to perform next simulation.
     * @return true for reusable, false for not reusable.
     */
    virtual bool isReusable() = 0;
};


#endif //PNOHS_MODE_ADAPTER_H
