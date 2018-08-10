//
// Created by genshen on 6/30/18.
//

#include "s_context.h"

SContext::SContext(unsigned long total_steps) : _total_steps(total_steps) {
    pNodesPool = new NodesPool();
}

SContext::SContext(NodesPool *pool, unsigned long total_steps) : _total_steps(total_steps), pNodesPool(pool) {}

SContext::~SContext() {
    delete pNodesPool; // fixme delete not here if NodesPool is not create by SContext.
}

