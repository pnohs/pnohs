//
// Created by genshen on 7/1/18.
//

#include <chrono>
#include <thread>
#include "runoff_adapter.h"

void RunoffAdapter::exec(ModelContext *p_context) {
    // p_context->flow += 1.0; // todo just an example.
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
}
