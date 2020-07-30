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

TEST(params_list_test_get_count, params_list_test) {
    TestParamsList list;
    EXPECT_EQ(list.getParamsSize(), 3);
}

// test params binding in class statically.
class TestParamsList2 : public ParamsList<3, 1> {
public:
    double &P1 = data[0].float_param;
};

// set params metadata
template<>
const std::array<param_meta, 3> TestParamsList::base_type_with_meta::metadata_list = {
        param_meta{param_type::float_tp, "A", {0.0}, {1.0}},
        param_meta{param_type::float_tp, "B", {0.0}, {1.0}},
        param_meta{param_type::float_tp, "C", {0.0}, {1.0}},
};

TEST(params_list_test_params_name, params_list_test) {
    TestParamsList2 list;
    list.P1 = 2;
    EXPECT_DOUBLE_EQ(list.P1, 2);
    EXPECT_DOUBLE_EQ(list.data[0].float_param, 2);
}

// test set params by key-value map.
TEST(set_value_by_map, params_list_test) {
    TestParamsList2 list;
    list.P1 = 1;
    list.data[1].float_param = 2;
    list.data[3].float_param = 3;

    std::map<std::string, param_const> params = {
            {"A", param_const{4}},
            {"B", param_const{5}},
            {"C", param_const{6}},
    };
    list.setValuesMap(params);
    EXPECT_EQ(list.data[0].float_param, 4);
    EXPECT_EQ(list.data[1].float_param, 5);
    EXPECT_EQ(list.data[2].float_param, 6);
}

// just a compiling test.
TEST(set_value_by_array, params_list_test) {
    TestParamsList2 list;
    list.P1 = 1;
    list.data[1].float_param = 2;
    list.data[3].float_param = 3;

    std::array<param_const, 3> params = {param_const{4}, param_const{5}, param_const{6}};
    list.setValues(params);

    EXPECT_EQ(list.data[0].float_param, 4);
    EXPECT_EQ(list.data[1].float_param, 5);
    EXPECT_EQ(list.data[2].float_param, 6);
}
