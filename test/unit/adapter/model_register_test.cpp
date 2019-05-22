//
// Created by genshen <genshenchu@gmail.com> on 2018/11/5.
//

#include <gtest/gtest.h>
#include <adapter/model_register.h>

class ModelA : public ModelRegister::RunoffInterface, RunoffAdapter {
public:
    RunoffAdapter *onReused(bool reusable) override { return nullptr; };

    void onBind(ModelContext *p_model_context, _type_node_id node_id) override {};

    void onParamsPassed(ModelContext *p_model_context, param_const params[], size_t size) override {};

    void exec(ModelContext *p_context, unsigned long time_steps) override {
        t = time_steps;
    };

    bool isReusable() override { return false; };

    static RunoffAdapter *newInstance() {
        return new ModelA();
    }

    FRIEND_TEST(instance_test, model_register);

private:
    unsigned long t = 0;
};

TEST(get_id_by_model_key, model_register) {
    ModelRegister::registerRunoffModel("a", ModelA::newInstance);
    ModelRegister::registerRunoffModel("b", ModelA::newInstance);
    _type_model_id id = ModelRegister::getModelIdByKey("a");
    EXPECT_EQ(id, 1);
    EXPECT_EQ(ModelRegister::getModelIdByKey("b"), 2);
    // un register test
    ModelRegister::unRegisterRunoffModel(id);
    EXPECT_EQ(ModelRegister::getModelIdByKey("a"), ModelRegister::MODEL_ID_NULL);
    EXPECT_EQ(ModelRegister::getModelIdByKey("b"), 2);
}

TEST(instance_test, model_register) {
    // register model
    ModelRegister::registerRunoffModel("a", ModelA::newInstance);
    // get model id by model name/key.
    _type_model_id id = ModelRegister::getModelIdByKey("a");
    // get a new model instance by model id.
    RunoffAdapter *a = ModelRegister::newInstanceRunoff(id);
    a->exec(nullptr, 9); // test running the model.
    EXPECT_EQ(((ModelA *) a)->t, 9);
}
