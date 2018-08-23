enable_testing()

if (NOT (PNOHS_MPI_ENABLE_FLAG))
    set(PNOHS_TEST_MPI_ENABLE_FLAG OFF)  # if we disabled MPI_ENABLE_FLAG,we cann't also use TEST_MPI_ENABLE_FLAG.
endif ()
MESSAGE(STATUS "MPI in test: ${PNOHS_TEST_MPI_ENABLE_FLAG}")

# Standard linking to gtest stuff.
set(PNOHS_EXTRA_LIBS gtest gtest_main ${PNOHS_EXTRA_LIBS})
MESSAGE(STATUS "Set googletest as test library.")

add_subdirectory(unit)
