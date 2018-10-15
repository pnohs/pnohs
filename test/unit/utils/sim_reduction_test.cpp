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

class SimReductionTest2 : public SimReduction<int> {
public:
    SimReductionTest2() : SimReduction(SimReductionTest::BUFFER_FLAG_NONE) {} // no buffer

    bool filter(const _type_node_id id, const unsigned long time_step) override {
        return true;
    }

    FRIEND_TEST(sim_reduction_test_flat, sim_reduction_test);

    FRIEND_TEST(sim_reduction_test_flat_node, sim_reduction_test);
};

TEST(sim_reduction_test_filter, sim_reduction_test) {
    SimReductionTest simTest;
    const unsigned int ids = 10, ts = 30;
    for (unsigned int id = 0; id < ids; id++) {
        for (unsigned int t = 0; t < ts; t++) {
            int res = id * 10 + t;
            simTest.OnOneStep(id, t, res);
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

TEST(sim_reduction_test_flat, sim_reduction_test) {
    SimReductionTest2 simTest;
    const unsigned int ids = 10, ts = 30;
    for (unsigned int id = 0; id < ids; id++) {
        for (unsigned int t = 0; t < ts; t++) {
            int res = id * 10 + t;
            simTest.OnOneStep(id, t, res);
        }
    }
    // now, map size will be 10 and each element in map is a vector with size 30.
    int *flows = new int[ids * ts];
    simTest.flat(flows, ids * ts, ts);
    // test
    int i = 0;
    for (unsigned int id = 0; id < ids; id++) {
        for (unsigned int t = 0; t < ts; t++) {
            int res = id * 10 + t; // the same as above
            EXPECT_EQ(flows[i], res);
            i++;
        }
    }
    delete flows;
}

TEST(sim_reduction_test_flat_node, sim_reduction_test) {
    SimReductionTest2 simTest;
    const unsigned int ids = 10, ts = 30;
    for (unsigned int id = 0; id < ids; id++) {
        for (unsigned int t = 0; t < ts; t++) {
            int res = id * 10 + t;
            simTest.OnOneStep(id, t, res);
        }
    }
    int a[ts];
    const unsigned int &data_len = ts;
    EXPECT_EQ(simTest.flatNode(a, 11, data_len), false); // id not exists
    EXPECT_EQ(simTest.flatNode(a, 2, data_len), true); // id = 2 exists
    for (int i = 0; i < data_len; i++) {
        EXPECT_EQ(a[i], 2 * 10 + i); // id = 2
    }
    EXPECT_EQ(simTest.flatNode(a, 2, data_len + 1), false); // len not match
    EXPECT_EQ(simTest.flatNode(a, 11, data_len + 1), false); // id not exists  & len not match
}
