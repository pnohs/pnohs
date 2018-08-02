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
    void stashUpstreamRouting(std::list<TypeRouting> &routing_data);

    void exec(ModelContext *p_context, unsigned long time_steps) override;

protected:
    std::list<TypeRouting> upstream_routing; // todo temp variable
};


#endif //PNOHS_ROUTING_ADAPTER_H
