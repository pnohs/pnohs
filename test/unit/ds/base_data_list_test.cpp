//
// Created by genshen on 8/14/18.
//

#include <ds/base_data_list.hpp>
#include <gtest/gtest.h>

// test params binding in params class constructor.
class TestBaseDataList : public BaseDataList<double, 3> {
public:
    double &P1, &P2, &P3;

    // bind ref and data in constructor
    TestBaseDataList(double p1, double p2, double p3) :
            BaseDataList(), P1(data[0]), P2(data[1]), P3(data[2]) {
        P1 = p1, P2 = p2, P3 = p3;
    }
};

TEST(base_data_list_test_data_reference, base_data_list_test) {
    TestBaseDataList list(3.14, 1.141421, 1.732);
    // test P0~P2
    EXPECT_DOUBLE_EQ(list.P1, 3.14);
    EXPECT_DOUBLE_EQ(list.P2, 1.141421);
    EXPECT_DOUBLE_EQ(list.P3, 1.732);
    // test data
    EXPECT_DOUBLE_EQ(list.data.at(0), 3.14);
    EXPECT_DOUBLE_EQ(list.data.at(1), 1.141421);
    EXPECT_DOUBLE_EQ(list.data.at(2), 1.732);

    // test data
    std::array<double, 3> params_data = {-3.14, -1.141421, -1.732};
    list.setValues(params_data);

    // test P0~P2
    EXPECT_DOUBLE_EQ(list.P1, -3.14);
    EXPECT_DOUBLE_EQ(list.P2, -1.141421);
    EXPECT_DOUBLE_EQ(list.P3, -1.732);
}

TEST(base_data_list_test_copy, base_data_list_test) {
    TestBaseDataList list(1, 2, 3);
    double d[] = {4, 5, 6, 7, 8, 9};
    list.setValues(d, 6); // 100 is more then the size of list.data 3.

    EXPECT_DOUBLE_EQ(list.data.at(0), 4);
    EXPECT_DOUBLE_EQ(list.data.at(1), 5);
    EXPECT_DOUBLE_EQ(list.data.at(2), 6);

    EXPECT_DOUBLE_EQ(list.P1, 4);
    EXPECT_DOUBLE_EQ(list.P2, 5);
    EXPECT_DOUBLE_EQ(list.P3, 6);
}

// bind ref and data in definition
class TestBaseDataList2 : public BaseDataList<double, 3> {
public:
    double &P1 = data[0];
    double &P2 = data[1];
    double &P3 = data[2];
};

TEST(base_data_list2_test_data_reference, base_data_list_test) {
    TestBaseDataList2 list = {};
    std::array<double, 3> params_data = {3.14, 1.141421, 1.732};
    list.setValues(params_data);

    // test P0~P2
    EXPECT_DOUBLE_EQ(list.P1, 3.14);
    EXPECT_DOUBLE_EQ(list.P2, 1.141421);
    EXPECT_DOUBLE_EQ(list.P3, 1.732);
    // test data
    EXPECT_DOUBLE_EQ(list.data.at(0), 3.14);
    EXPECT_DOUBLE_EQ(list.data.at(1), 1.141421);
    EXPECT_DOUBLE_EQ(list.data.at(2), 1.732);
}

TEST(base_data_list2_test_copy, base_data_list_test) {
    TestBaseDataList2 list = {};
    std::array<double, 3> params_data = {1, 2, 3};
    list.setValues(params_data);

    double d[] = {4, 5, 6, 7, 8, 9};
    list.setValues(d, 6); // 100 is more then the size of list.data 3.

    EXPECT_DOUBLE_EQ(list.data.at(0), 4);
    EXPECT_DOUBLE_EQ(list.data.at(1), 5);
    EXPECT_DOUBLE_EQ(list.data.at(2), 6);

    EXPECT_DOUBLE_EQ(list.P1, 4);
    EXPECT_DOUBLE_EQ(list.P2, 5);
    EXPECT_DOUBLE_EQ(list.P3, 6);
}
