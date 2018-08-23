//
// Created by genshen on 2018/03/20.
//

#include <gtest/gtest.h>
#include <test/gtest_env.h>
#include "test_config.h"

// see https://github.com/google/googletest/issues/822 for more information.
// main function for adapt mpi environment
int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
#ifdef PNOHS_TEST_MPI_ENABLE_FLAG
    ::testing::AddGlobalTestEnvironment(new kiwi::MPIEnvironment);
#endif  // end TEST_MPI_ENABLE_FLAG
    return RUN_ALL_TESTS();
}
