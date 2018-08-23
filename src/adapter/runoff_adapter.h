//
// Created by genshen on 7/1/18.
//

#ifndef PNOHS_RUNOFF_ADAPTER_H
#define PNOHS_RUNOFF_ADAPTER_H

#include "model_context.h"
#include "model_adapter.h"

class RunoffAdapter : public ModelAdapter {
public:
    virtual ~RunoffAdapter();

    void exec(ModelContext *p_context, unsigned long time_steps) override;

    /**
     * in this method, if the model is reusable, this runoff model should be reset to performing next simulation;
     * otherwise(non reusable mode), a new runoff model should be created to performing next simulation.
     * @note in non reusable mode, the old RoutingAdapter instance will automatically destroyed after new instant is created.
     * @return current RunoffAdapter(for recyclable) or new RunoffAdapter(for non-recyclable).
     */
    virtual RunoffAdapter *onReused(bool reusable) = 0;
};

#endif //PNOHS_RUNOFF_ADAPTER_H
