//
// Created by genshen on 7/1/18.
//

#ifndef PNOHS_RUNOFF_ADAPTER_H
#define PNOHS_RUNOFF_ADAPTER_H

#include "model_context.h"
#include "model_adapter.h"

class RunoffAdapter : public ModelAdapter {
public:
    void exec(ModelContext *p_context) override;
};


#endif //PNOHS_RUNOFF_ADAPTER_H
