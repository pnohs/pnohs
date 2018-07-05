//
// Created by genshen on 3/27/18.
//

#include <list>
#include "routing_adapter.h"

void RoutingAdapter::stashUpstreamRouting(std::list<TypeRouting> &routing_data) {
    upstream_routing = routing_data;
}

void RoutingAdapter::exec(ModelContext *p_context) {
    for (TypeRouting &r:upstream_routing) {
        p_context->flow += r.routing_data; // todo just an example.
    }
}
