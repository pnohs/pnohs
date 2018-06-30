//
// Created by genshen on 6/30/18.
//

#include "s_context.h"

SContext::SContext(unsigned long total_steps): _total_steps(total_steps)  {
    printf("OKKKK%d\n",_total_steps);
    pNodesPool = new NodesPool();
}

SContext::~SContext() {
    delete pNodesPool;
}
