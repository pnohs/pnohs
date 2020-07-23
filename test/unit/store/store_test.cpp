//
// Created by genshen on 2020/7/23.
//

#include <string>
#include <gtest/gtest.h>
#include <fstream>

#include "store/store_writer.hpp"
#include "store/store_reader.hpp"

#include "../test_config.h"

const std::string store_bin_file = PNOHS_TEST_TEMP_STORAGE_PATH "/store_test.bin";

struct TestStoreDataType {
    int a;
    double d;
    char c;
};

TEST(store_test_read_write, store_test) {
    std::fstream fsw(store_bin_file, std::ios::out | std::ios::binary);
    StoreWriter<int, TestStoreDataType> writer(fsw, 4);
    std::vector<int> ids = {0, 1, 4, 2};
    std::vector<TestStoreDataType> data = {
            {1, 10.0, 'A'},
            {2, 20.0, 'B'},
            {3, 30.0, 'C'},
            {4, 40.0, 'D'},
    };
    writer.write(ids.data(), data.data(), 4);
    writer.done();
    fsw.close();

    // read
    std::fstream fsr(store_bin_file, std::ios::in | std::ios::binary);
    StoreReader<int, TestStoreDataType> reader(fsr);

    EXPECT_EQ(reader.getBlockCount(), 4);
    TestStoreDataType block;

    reader.read(0, &block);
    EXPECT_EQ(block.c, data[0].c); // 'A'

    reader.read(2, &block);
    EXPECT_EQ(block.c, data[3].c); // 'D'

    reader.read(1, &block);
    EXPECT_EQ(block.c, data[1].c); // 'B'

    reader.read(4, &block);
    EXPECT_EQ(block.c, data[2].c); // 'C'

    // expect not found throw
    EXPECT_ANY_THROW(reader.read(3, &block));
}
