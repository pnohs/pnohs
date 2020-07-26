//
// Created by genshen on 2020/7/23.
//

#include <string>
#include <gtest/gtest.h>
#include <fstream>
#include <store/2d_store_reader.hpp>

#include "store/store_writer.hpp"
#include "store/store_reader.hpp"
#include "store/2d_store_writer.hpp"

#include "../test_config.h"

const std::string store_bin_file = PNOHS_TEST_TEMP_STORAGE_PATH "/store_test.bin";
const std::string store_2d_bin_file = PNOHS_TEST_TEMP_STORAGE_PATH "/store2d_test.bin";

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

TEST(store_test_read_write_2d, store_test) {
    std::fstream fsw(store_2d_bin_file, std::ios::out | std::ios::binary);
    StoreWriter2D<int, TestStoreDataType> writer(fsw, 4);
    std::vector<TestStoreDataType> block1 = {
            {1, 10.0, 'A'},
    };
    std::vector<TestStoreDataType> block2 = {
            {2, 20.0, 'B'},
    };
    std::vector<TestStoreDataType> block3 = {
            {3, 30.0, 'C'},
            {4, 40.0, 'D'},
    };
    std::vector<TestStoreDataType> block4 = {
            {5, 50.0, 'E'},
            {6, 60.0, 'F'},
    };
    std::vector<int> ids = {0, 1, 4, 2};
    writer.write(ids[0], block1.data(), block1.size());
    writer.write(ids[1], block2.data(), block2.size());
    writer.write(ids[2], block3.data(), block3.size());
    writer.write(ids[3], block4.data(), block4.size());
    writer.done();
    fsw.close();

    // then we read the file
    std::fstream fsr(store_2d_bin_file, std::ios::in | std::ios::binary);
    StoreReader2D<int, TestStoreDataType> reader(fsr);
    TestStoreDataType sub_blocks[2]; // save data of sub blocks in a block

    EXPECT_EQ(reader.getBlockCount(), 4);

    reader.read(0, sub_blocks);
    EXPECT_EQ(reader.getBlockMeta(0).sub_blocks_num, 1);
    EXPECT_EQ(sub_blocks[0].c, 'A');

    reader.read(1, sub_blocks);
    EXPECT_EQ(reader.getBlockMeta(1).sub_blocks_num, 1);
    EXPECT_EQ(sub_blocks[0].c, 'B');

    reader.read(4, sub_blocks);
    EXPECT_EQ(reader.getBlockMeta(4).sub_blocks_num, 2);
    EXPECT_EQ(sub_blocks[0].c, 'C');
    EXPECT_EQ(sub_blocks[1].c, 'D');

    reader.read(2, sub_blocks);
    EXPECT_EQ(reader.getBlockMeta(2).sub_blocks_num, 2);
    EXPECT_EQ(sub_blocks[0].c, 'E');
    EXPECT_EQ(sub_blocks[1].c, 'F');

    // test part read, case 1
    reader.read(4, sub_blocks, 1);
    EXPECT_EQ(sub_blocks[0].c, 'C');
    EXPECT_EQ(sub_blocks[1].c, 'F'); // not change

    // test part read, case 2: large size. Expect read 2 sub-blocks.
    reader.read(4, sub_blocks, 100);
    EXPECT_EQ(sub_blocks[0].c, 'C');
    EXPECT_EQ(sub_blocks[1].c, 'D');
}
