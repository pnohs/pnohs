//
// Created by genshen on 7/2/18.
//

#ifndef PNOHS_MODE_ADAPTER_H
#define PNOHS_MODE_ADAPTER_H

#include "model_context.h"

/**
 * the common methods used in routing model and runoff mode, are declared here.
 */
class ModelAdapter {
public:

    /*
     * run the model.
     */
    virtual void exec(ModelContext *p_context)= 0;
};

#endif //PNOHS_MODE_ADAPTER_H
