
MESSAGE(STATUS "Set googletest as test library.")

# configure a header file to pass some of the CMake settings to the source code
configure_file(
        "${PROJECT_SOURCE_DIR}/test/unit/test_config.h.in"
        "${PROJECT_SOURCE_DIR}/test/unit/test_config.h"
)


################################
# googletest:gtest and mocktest
################################
# or using ExternalProject_Add, see:https://github.com/kaizouman/gtest-cmake-example

# download googletest from https://github.com/google/googletest/,and copy it to "external" directory.
# Include the gtest library. gtest_SOURCE_DIR is available due to 'project(gtest)' above.
# an issue for mingw on winodws, see: https://github.com/google/googletest/issues/606#issuecomment-234733757
add_subdirectory(${PROJECT_SOURCE_DIR}/vendor/src/googletest/googletest ${PROJECT_BINARY_DIR}/vendor/googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

#googlemock
#add_subdirectory("${source_dir}/googlemock")
#include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})

# Standard linking to gtest stuff.
set(EXTRA_LIBS ${EXTRA_LIBS} gtest gtest_main)
## end of google test


#########################
# Unit Tests Settings
#########################
include_directories(${PROJECT_SOURCE_DIR}/vendor/include)
include_directories(${PROJECT_SOURCE_DIR}/src)

set(TEST_HEADER_FILES
        test_config.h
        gtest_env.h
        )

set(TEST_SOURCE_FILES
        main.cpp
        app_test.cpp
        )

# set binary path and lib storage path wile compiling process.
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

add_executable(${M_UINT_TEST_NAME} ${TEST_SOURCE_FILES} ${TEST_HEADER_FILES})

# Extra linking for the project.
set(EXTRA_LIBS ${EXTRA_LIBS} ${M_LIB_NAME})
# Extra linking for the project.
target_link_libraries(${M_UINT_TEST_NAME} ${EXTRA_LIBS})

# This is so you can do 'make test' to see all your tests run, instead of
# manually running the executable runUnitTests to see those specific tests.
add_test(NAME exampleTests COMMAND ${M_UINT_TEST_NAME})


##########################
##### install files
##########################
install(TARGETS ${M_UINT_TEST_NAME}
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        )
