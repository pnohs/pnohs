//
// Created by genshen on 8/2/18.
//
#include <gtest/gtest.h>
#include <simulation_node.h>

class SimpleCtx : public ModelContext {
public:
    param_tp_float P_A;
    bool is_bind = false;

    ~SimpleCtx() override = default;

    void onBind(const _type_node_id node_id) {
        is_bind = true;
    }

    bool isRecyclable() override { return true; }

    ModelContext *onRecycle(bool) override { return this; }
};

class SimpleRunOffModel : public RunoffAdapter {
public:
    bool bind_test = false;

    ~SimpleRunOffModel() override = default;

    void onBind(ModelContext *p_model_context, _type_node_id node_id) override {
        bind_test = true;
    }

    void onParamsPassed(ModelContext *p_model_context, param_const params[], size_t size) override {
        ((SimpleCtx *) p_model_context)->P_A = params[0].float_param;
    }

    void exec(ModelContext *p_context, unsigned long time_steps) override {
        ((SimpleCtx *) p_context)->P_A += 3.0; // change param.
    }

    bool isReusable() override { return true; }

    SimpleRunOffModel *onReused(bool) override { return this; }
};

TEST(model_adapter_test_create, model_adapter_test) {
    // create a simulation node.
    SimulationNode s_node(0x123);
    SimpleCtx simpleCtx;
    SimpleRunOffModel runoff;

    // set context firstly, or context can be null.
    s_node.setModelContext(&simpleCtx);

    // set model
    s_node.setModelRunoff(&runoff);

    // set params
    param_const params[] = {1.2};
    runoff.onParamsPassed(&simpleCtx, params, 1);

    // simulate
    s_node.runoff();

    EXPECT_EQ(runoff.bind_test, true); // on bind called.
    EXPECT_EQ(simpleCtx.is_bind, true); // on context bind called.
    EXPECT_FLOAT_EQ(simpleCtx.P_A, 1.2 + 3.0);
}
