//
// Created by genshen on 2017/12/24.
//

#ifndef PNOHS_CATCH2_TEST_ENV_H
#  define PNOHS_CATCH2_TEST_ENV_H
#  define CATCH_CONFIG_RUNNER

#  include "catch.hpp"
#  include <iostream>

#  ifdef TEST_MPI_ENABLE_FLAG
#    include "mpi.h"
#  endif  // end TEST_MPI_ENABLE_FLAG

int main(int argc, char *argv[]) {
    // global setup...
#ifdef TEST_MPI_ENABLE_FLAG
    // Initialize the MPI environment.
    MPI_Init(NULL, NULL);
    std::cout<<"initialed mpi.";
#endif  // end TEST_MPI_ENABLE_FLAG

    int result = Catch::Session().run(argc, argv);

// global clean-up...
#ifdef TEST_MPI_ENABLE_FLAG
    // Finalize the MPI environment.
    MPI_Finalize();
#endif  // end TEST_MPI_ENABLE_FLAG

    return result;
}

#endif // PNOHS_CATCH2_TEST_ENV_H
