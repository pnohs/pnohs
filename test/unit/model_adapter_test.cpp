//
// Created by genshen on 8/2/18.
//
#include <gtest/gtest.h>
#include <simulation_node.h>

class SimpleCtx : public ModelContext {
public:
    param_const P_A;
};

class SimpleRunOffModel : public RunoffAdapter {
public:
    bool bind_test = false;

    void onBind(ModelContext *p_model_context, _type_node_id node_id) override {
        bind_test = true;
    }

    void onParamsPassed(ModelContext *p_model_context, param_const params[]) override {
        ((SimpleCtx *) p_model_context)->P_A = params[0];
    }

    void exec(ModelContext *p_context, unsigned long time_steps) override {
        ((SimpleCtx *) p_context)->P_A += 3.0; // change param.
    }
};

TEST(model_adapter_test_create, model_adapter_test) {
    // create a simulation node.
    SimulationNode s_node;
    SimpleCtx simpleCtx;
    SimpleRunOffModel runoff;

    // set context firstly, or context can be null.
    s_node.setModelContext(&simpleCtx);

    // set model
    s_node.setModelRunoff(&runoff);

    // set params
    param_const params[] = {1.2};
    runoff.onParamsPassed(&simpleCtx, params);

    // simulate
    s_node.runoff();

    EXPECT_EQ(runoff.bind_test, true); // on bind called.
    EXPECT_FLOAT_EQ(simpleCtx.P_A, 1.2 + 3.0);
}