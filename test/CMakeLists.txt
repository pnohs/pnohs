enable_testing()

set(TEST_LIBRARY_TO_USE "catch2" CACHE STRING "test library selected at CMake configure time,googletest or catch2")
set_property(CACHE TEST_LIBRARY_TO_USE PROPERTY STRINGS googletest catch2)
MESSAGE(STATUS "Set ${TEST_LIBRARY_TO_USE} as test library.")
if (${TEST_LIBRARY_TO_USE} MATCHES "googletest")
    set(GOOGLE_TEST_ENABLE_FLAG ON)
else ()
    set(CATCH2_TEST_ENABLE_FLAG ON)
endif ()

if (NOT (MPI_ENABLE_FLAG))
    set(TEST_MPI_ENABLE_FLAG OFF)  # if we disabled MPI_ENABLE_FLAG,we cann't also use TEST_MPI_ENABLE_FLAG.
endif ()
MESSAGE(STATUS "MPI in test: ${TEST_MPI_ENABLE_FLAG}")

# configure a header file to pass some of the CMake settings to the source code
configure_file(
        "${PROJECT_SOURCE_DIR}/test/test_config.h.in"
        "${PROJECT_SOURCE_DIR}/test/test_config.h"
)

################################
# googletest:gtest and mocktest
################################
if (GOOGLE_TEST_ENABLE_FLAG)
    # or using ExternalProject_Add, see:https://github.com/kaizouman/gtest-cmake-example

    # download googletest from https://github.com/google/googletest/,and copy it to "external" directory.
    # Include the gtest library. gtest_SOURCE_DIR is available due to 'project(gtest)' above.
    # an issue for mingw on winodws, see: https://github.com/google/googletest/issues/606#issuecomment-234733757
    add_subdirectory("external/googletest/googletest")
    include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

    #googlemock
    #add_subdirectory("${source_dir}/googlemock")
    #include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})

    #### end for googletest
    # Standard linking to gtest stuff.
    set(EXTRA_LIBS ${EXTRA_LIBS} gtest gtest_main)
endif ()

################################
# Catch2: https://github.com/catchorg/Catch2
################################
if (CATCH2_TEST_ENABLE_FLAG)
    include_directories("external/catch2")
endif ()

#########################
# Unit Tests Settings
#########################
set(TEST_SOURCE_FILES
        main.cpp
        app_test.cpp
        )

include_directories(${PROJECT_SOURCE_DIR}/src)

add_executable(unitTests ${TEST_SOURCE_FILES})

# Extra linking for the project.
target_link_libraries(unitTests ${LIB_NAME_SRC} ${EXTRA_LIBS})

# This is so you can do 'make test' to see all your tests run, instead of
# manually running the executable runUnitTests to see those specific tests.
add_test(NAME exampleTests COMMAND unitTests)
