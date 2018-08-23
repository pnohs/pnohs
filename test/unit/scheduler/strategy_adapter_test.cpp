//
// Created by genshen on 8/4/18.
//

#include <gtest/gtest.h>
#include <scheduler/strategy_adapter.h>
#include <scheduler/strategy_container.h>

class StrategyAdapterForTest : public StrategyAdapter {
public:
    StrategyAdapterForTest(SContext &context) : StrategyAdapter(context) {};

    SimulationNode *pickRunnable() override { return nullptr; }
};

TEST(adapter_momery_destroy, strategy_adapter_test) {
    SContext ctx(1);
    // use direct object can cause: signal 11: SIGSEGV, pointer is ok.
    StrategyContainer::registerStrategy("key1", new StrategyAdapterForTest(ctx));
    EXPECT_EQ(StrategyContainer::strategies(), 1);
    StrategyContainer::destroyAllStrategies();
}

TEST(adapter_momery_add_multiple_and_destroy_test, strategy_adapter_test) {
    SContext ctx(1);
    // use direct object can cause: signal 11: SIGSEGV, pointer is ok.
    StrategyContainer::registerStrategy("key1", new StrategyAdapterForTest(ctx));
    StrategyContainer::registerStrategy("key1", new StrategyAdapterForTest(ctx));
    EXPECT_EQ(StrategyContainer::strategies(), 1);
    StrategyContainer::destroyAllStrategies();
}

TEST(adapter_momery_add_multiple_and_destroy2_test, strategy_adapter_test) {
    SContext ctx(1);
    for (int i = 0; i < 10; i++) {
        StrategyContainer::registerStrategy("key1", new StrategyAdapterForTest(ctx));
        StrategyContainer::registerStrategy("key2", new StrategyAdapterForTest(ctx));
        StrategyContainer::destroyAllStrategies();
    }
}
