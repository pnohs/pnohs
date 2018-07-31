enable_testing()

if (NOT (PNOHS_MPI_ENABLE_FLAG))
    set(PNOHS_TEST_MPI_ENABLE_FLAG OFF)  # if we disabled MPI_ENABLE_FLAG,we cann't also use TEST_MPI_ENABLE_FLAG.
endif ()
MESSAGE(STATUS "MPI in test: ${PNOHS_TEST_MPI_ENABLE_FLAG}")

# set(TEST_LIBRARY_TO_USE "catch2" CACHE STRING "test library selected at CMake configure time,googletest or catch2")
# set_property(CACHE TEST_LIBRARY_TO_USE PROPERTY STRINGS googletest catch2)
# if (${TEST_LIBRARY_TO_USE} MATCHES "googletest")
#     set(GOOGLE_TEST_ENABLE_FLAG ON)
# else ()
#     set(CATCH2_TEST_ENABLE_FLAG ON)
# endif ()


################################
# googletest:gtest and mocktest
################################
# or using ExternalProject_Add, see:https://github.com/kaizouman/gtest-cmake-example

# download googletest from https://github.com/google/googletest/,and copy it to "external" directory.
# Include the gtest library. gtest_SOURCE_DIR is available due to 'project(gtest)' above.
# an issue for mingw on winodws, see: https://github.com/google/googletest/issues/606#issuecomment-234733757
if (NOT TARGET gtest)
    add_subdirectory(${CMAKE_SOURCE_DIR}/vendor/src/googletest/googletest ${PROJECT_BINARY_DIR}/vendor/googletest)
endif ()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

#googlemock
#add_subdirectory("${source_dir}/googlemock")
#include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})

# Standard linking to gtest stuff.
set(PNOHS_EXTRA_LIBS gtest gtest_main ${PNOHS_EXTRA_LIBS})
MESSAGE(STATUS "Set googletest as test library.")

add_subdirectory(unit)
