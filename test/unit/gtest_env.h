//
// Created by genshen on 2018/03/20.
//

#ifndef PNOHS_GTEST_ENV_H
#define PNOHS_GTEST_ENV_H
#include <gtest/gtest.h>

#  ifdef TEST_MPI_ENABLE_FLAG
#    include "mpi.h"


class MPIEnvironment : public ::testing::Environment {
public:
    virtual void SetUp() {
        char **argv;
        int argc = 0;
        int mpiError = MPI_Init(&argc, &argv);
        ASSERT_FALSE(mpiError);
    }

    virtual void TearDown() {
        int mpiError = MPI_Finalize();
        ASSERT_FALSE(mpiError);
    }

    virtual ~MPIEnvironment() {}
};
#  endif  // end TEST_MPI_ENABLE_FLAG

#endif // PNOHS_GTEST_ENV_H
