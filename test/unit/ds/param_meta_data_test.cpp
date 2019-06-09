//
// Created by genshen on 2019-06-09.
//

#include <gtest/gtest.h>
#include <ds/params_list.hpp>

// test params binding in class statically.
class ParamsListMetaTest : public ParamsList<3, 4> {
public:
    double &P1 = data[0].float_param;
    double &P2 = data[1].float_param;
    double &P3 = data[2].float_param;
};

// set params metadata
template<>
const std::array<param_meta, 3> ParamsListMetaTest::ParamsList<3, 4>::metadata_list = {
        param_meta{param_type::float_tp, "A", {0.0}, {1.0}},
        param_meta{param_type::float_tp, "B", {0.0}, {1.0}},
        param_meta{param_type::float_tp, "C", {0.0}, {1.0}},
};

TEST(params_metadata_getKeys, params_list_test) {
    std::string keys[3];
    ParamsListMetaTest::getKeys(keys);
    EXPECT_EQ(keys[0],"A");
    EXPECT_EQ(keys[1],"B");
    EXPECT_EQ(keys[2],"C");
}
