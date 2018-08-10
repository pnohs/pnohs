//
// Created by genshen on 3/27/18.
//

#ifndef PNOHS_ROUTING_ADAPTER_H
#define PNOHS_ROUTING_ADAPTER_H

#include <list>
#include "../adapter/type_routing.h"
#include "model_adapter.h"
#include "model_context.h"

class RoutingAdapter : public ModelAdapter {
public:
    virtual ~RoutingAdapter() override = default;

    void stashUpstreamRouting(std::list<TypeRouting> &routing_data);

    void exec(ModelContext *p_context, unsigned long time_steps) override;

    /**
     * in this method, if the model is reusable, this routing model should be reset to performing next simulation;
     * otherwise(non reusable mode), a new routing model should be created to performing next simulation.
     * @note in non reusable mode, the old RoutingAdapter instance will automatically destroyed after new instant is created.
     * @return current RoutingAdapter(for recyclable) or new RoutingAdapter(for non-recyclable).
     */
    virtual RoutingAdapter *onReused(bool reusable) = 0;

protected:
    std::list<TypeRouting> upstream_routing; // todo temp variable
};


#endif //PNOHS_ROUTING_ADAPTER_H
