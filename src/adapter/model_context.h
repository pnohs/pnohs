//
// Created by genshen on 7/2/18.
//

#ifndef PNOHS_MODEL_CONTEXT_H
#define PNOHS_MODEL_CONTEXT_H

/**
 * Model Context is used in simulation for passing node information (e.g. area of simulation node.)
 * to runoff model and river routing mode.
 */
class ModelContext {
public:
    double area; // todo example property of this node.
    double flow;

    ModelContext();
};


#endif //PNOHS_MODEL_CONTEXT_H
