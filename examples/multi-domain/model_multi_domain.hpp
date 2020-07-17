//
// Created by genshen on 2020/6/30.
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
        flow = 0.0; // reset flow of this node.
        return this;
    }

private:
    _type_node_id _id;
};

// runoff model with 1 parameter: param_rescale
class ExampleRunoffModel : public RunoffAdapter {
public:
    void onBind(ModelContext *p_model_context, _type_node_id node_id) override {}

    void onParamsPassed(ModelContext *p_model_context, param_const params[], size_t size) override {
        if (size >= 1) {
            param_rescale = params[0].float_param;
        }
    }

    const _type_params_count paramCount() override {
        return 1;
    }

    bool isReusable() override {
        return true;
    }

    RunoffAdapter *onReused(bool reusable) override {
        return this;
    }

    void exec(ModelContext *p_context, unsigned long time_steps) override {
        p_context->flow += 1.0 * param_rescale;
    }

    static RunoffAdapter *newInstance() {
        return new ExampleRunoffModel();
    }

private:
    param_tp_float param_rescale = 1.0;
};

// routing model with 1 parameter: param_rescale
class ExampleRoutingModel : public RoutingAdapter {
public:
    void onBind(ModelContext *p_model_context, _type_node_id node_id) override {}

    void onParamsPassed(ModelContext *p_model_context, param_const params[], size_t size) override {
        if (size >= 1) {
            param_rescale = params[0].float_param;
        }
    }

    const _type_params_count paramCount() override {
        return 1;
    }

    bool isReusable() override {
        return true;
    }

    RoutingAdapter *onReused(bool reusable) override {
        return this;
    }

    void exec(ModelContext *p_context, unsigned long time_steps) override {
        // add flow from upstream nodes
        double up_flows = 0.0;
        for (auto up : this->upstream_routing) {
            up_flows += up.routing_data[0];
        }
        p_context->flow += up_flows; // add flow of runoff model of this node, and flows of direct up streams.
        p_context->flow -= 0.5 * param_rescale; // cut flow of 0.5
    }

    static RoutingAdapter *newInstance() {
        return new ExampleRoutingModel();
    }

private:
    param_tp_float param_rescale = 1.0;
};
