//
// Created by genshen on 7/1/18.
//

#include <chrono>
#include <thread>
#include "runoff_adapter.h"

RunoffAdapter::~RunoffAdapter() = default;

void RunoffAdapter::exec(ModelContext *p_context, unsigned long time_steps) {
    // p_context->flow += 1.0; // todo just an example.
}
