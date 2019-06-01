//
// Created by genshen on 8/14/18.
//


#include <gtest/gtest.h>
#include <ds/params_list.hpp>

class TestParamsList : public ParamsList<3> {
    // it have 3 parameters.
};

TEST(params_list_test_get_count, params_list_test) {
    TestParamsList list;
    EXPECT_EQ(list.getParamsSize(), 3);
}

// test params binding in class statically.
class TestParamsList2 : public ParamsList<3> {
public:
    param_const &P1 = data[0];
};

TEST(params_list_test_params_name, params_list_test) {
    TestParamsList2 list;
    list.P1 = 2;
    EXPECT_DOUBLE_EQ(list.P1, 2);
    EXPECT_DOUBLE_EQ(list.data[0], 2);
}
