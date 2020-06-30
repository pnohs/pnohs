cmake_minimum_required(VERSION 3.0)

project(pnohs)

set(CMAKE_CXX_STANDARD 11)

include(config.cmake)
include(dependency.cmake)

add_subdirectory(src)

if (PNOHS_EXAMPLE_BUILD_ENABLE_FLAG)
    add_subdirectory(examples)
endif ()

if (PNOHS_TOOLS_BUILD_ENABLE_FLAG)
    add_subdirectory(tools)
endif ()
################################
## test configure
################################
if (PNOHS_TEST_BUILD_ENABLE_FLAG)
    MESSAGE(STATUS "TEST is enabled")
    enable_testing()
    add_subdirectory(test)
endif ()
