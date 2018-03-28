//
// Created by genshen on 3/28/18.
//

#include "context.h"

Context::Context(ConfigToml *pConfig) {
    this->pConfig = pConfig;
}


void Context::newTaskQueue() {

}

bool Context::select() {
    for (SimulationNode &sNode : simulationNodes) {
        if (sNode._time_steps <= pConfig->simulationTimeSteps
            && sNode.upstream.isReady()) { // todo
            curNode = &sNode;
            return true;
        }
    }
    return false;
}
