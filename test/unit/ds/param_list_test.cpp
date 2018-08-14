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
    EXPECT_DOUBLE_EQ(list.getParamsSize(), 3);
}
