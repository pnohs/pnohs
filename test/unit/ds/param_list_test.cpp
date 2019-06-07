//
// Created by genshen on 8/14/18.
//

#include <map>
#include <array>
#include <gtest/gtest.h>
#include <ds/params_list.hpp>

class TestParamsList : public ParamsList<3, 1> {
    // it have 3 parameters.
};

// set params keys/names
template<>
const std::array<std::string, 3> TestParamsList::ParamsList<3, 0>::keys = {"A", "B", "C"};

TEST(params_list_test_get_count, params_list_test) {
    TestParamsList list;
    EXPECT_EQ(list.getParamsSize(), 3);
}

// test params binding in class statically.
class TestParamsList2 : public ParamsList<3, 1> {
public:
    param_const &P1 = data[0];
};

// set params keys/names
template<>
const std::array<std::string, 3> TestParamsList2::ParamsList<3, 1>::keys = {"A", "B", "C"};

TEST(params_list_test_params_name, params_list_test) {
    TestParamsList2 list;
    list.P1 = 2;
    EXPECT_DOUBLE_EQ(list.P1, 2);
    EXPECT_DOUBLE_EQ(list.data[0], 2);
}

// test set params by key-value map.
TEST(set_value_by_map, params_list_test) {
    TestParamsList2 list;
    list.P1 = 1;
    list.data[1] = 2;
    list.data[3] = 3;

    std::map<std::string, param_const> params = {
            {"A", 4},
            {"B", 5},
            {"C", 6},
    };
    list.setValuesMap(params);
    EXPECT_EQ(list.data[0], 4);
    EXPECT_EQ(list.data[1], 5);
    EXPECT_EQ(list.data[2], 6);
}

// just a compiling test.
TEST(set_value_by_array, params_list_test) {
    TestParamsList2 list;
    list.P1 = 1;
    list.data[1] = 2;
    list.data[3] = 3;

    std::array<param_const, 3> params = {4, 5, 6};
    list.setValues(params);

    EXPECT_EQ(list.data[0], 4);
    EXPECT_EQ(list.data[1], 5);
    EXPECT_EQ(list.data[2], 6);
}
