//
// Created by genshen on 2020/6/13.
//

#include <adapter/model_context.h>
#include <adapter/runoff_adapter.h>

class ExampleContext : public ModelContext {
public:
    explicit ExampleContext(const _type_node_id &node_id) : _id(node_id) {}

    void onBind(const _type_node_id node_id) override {
        flow = 0.0;
        _id = node_id;
    }

    bool isRecyclable() override {
        return true;
    }

    ModelContext *onRecycle(bool recyclable) override {
        return this;
    }

private:
    _type_node_id _id;
};

// runoff model
class ExampleRunoffModel : public RunoffAdapter {
public:
    void onBind(ModelContext *p_model_context, _type_node_id node_id) override {}

    void onParamsPassed(ModelContext *p_model_context, param_const params[], size_t size) override {}

    bool isReusable() override {
        return true;
    }

    RunoffAdapter *onReused(bool reusable) override {
        return this;
    }

    void exec(ModelContext *p_context, unsigned long time_steps) override {
        p_context->flow += 0.01; // add 0.01 to flow.
    }

    static RunoffAdapter *newInstance() {
        return new ExampleRunoffModel();
    }
};

// routing model
class ExampleRoutingModel : public RoutingAdapter {
public:
    void onBind(ModelContext *p_model_context, _type_node_id node_id) override {}

    void onParamsPassed(ModelContext *p_model_context, param_const params[], size_t size) override {}

    bool isReusable() override {
        return true;
    }

    RoutingAdapter *onReused(bool reusable) override {
        return this;
    }

    void exec(ModelContext *p_context, unsigned long time_steps) override {
        p_context->flow += 1.0; // add 1.0 to flow.
    }

    static RoutingAdapter *newInstance() {
        return new ExampleRoutingModel();
    }
};
