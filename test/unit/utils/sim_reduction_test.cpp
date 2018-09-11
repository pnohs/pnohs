//
// Created by genshen on 9/11/18.
//

#include <utils/sim_reduction.hpp>
#include <gtest/gtest.h>

class SimReductionTest : public SimReduction<int> {
public:
    SimReductionTest() : SimReduction(SimReductionTest::BUFFER_FLAG_NONE) {} // no buffer

    bool filter(const _type_node_id id, const unsigned long time_step) override {
        return id % 2 == 0 && time_step % 2 == 0;
    }

    FRIEND_TEST(sim_reduction_test_filter, sim_reduction_test);
};

TEST(sim_reduction_test_filter, sim_reduction_test) {
    SimReductionTest simTest;
    const unsigned int ids = 10, ts = 30;
    for (unsigned int id = 0; id < ids; id++) {
        for (unsigned int t = 0; t < ts; t++) {
            int res = id * 10 + t;
            simTest.OnOneStep(res, id, t);
        }
    }

    EXPECT_EQ(simTest.r.size(), static_cast<unsigned long>(ids / 2));
    for (int id = 0; id < ids; id += 2) { // select all id in simTest.r
        unsigned int t = 0;
        for (int my_t : simTest.r[id]) {
            EXPECT_EQ(my_t, 10 * id + t);
            t += 2; // select all filtered-passed t.
        }
    }
}
