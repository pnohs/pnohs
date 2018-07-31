//
// Created by genshen on 2018/03/20.
//

#ifndef PNOHS_GTEST_ENV_H
#define PNOHS_GTEST_ENV_H
#include <gtest/gtest.h>
#include "test_config.h"

#ifdef PNOHS_TEST_MPI_ENABLE_FLAG
#include "mpi.h"

class MPIEnvironment : public ::testing::Environment {
public:
    void SetUp() override {
        char **argv;
        int argc = 0;
        int mpiError = MPI_Init(&argc, &argv);
        ASSERT_FALSE(mpiError);
    }

    void TearDown() override {
        int mpiError = MPI_Finalize();
        ASSERT_FALSE(mpiError);
    }

    ~MPIEnvironment() override = default;
};
#endif  // end PPNOHS_TEST_MPI_ENABLE_FLAG


#endif // PNOHS_GTEST_ENV_H
