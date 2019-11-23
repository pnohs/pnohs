//
// Created by genshen on 7/2/18.
//

#include "model_context.h"

ModelContext::ModelContext() : area(0) {

}

ModelContext::~ModelContext() = default;

void ModelContext::flowsToDownstream(TypeRouting::tp_routing_data *flows) {
    flows->emplace_back(flow);
}

void ModelContext::beforeStep() {

}
