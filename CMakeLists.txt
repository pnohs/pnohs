cmake_minimum_required(VERSION 3.0)

project(pnohs)

set(CMAKE_CXX_STANDARD 11)

include(config.cmake)
include(dependency.cmake)

add_subdirectory(src)

if (PNOHS_TOOLS_BUILD_ENABLE_FLAG)
    add_subdirectory(tools)
endif ()
################################
## test configure
################################
if (PNOHS_TEST_BUILD_ENABLE_FLAG)
    MESSAGE(STATUS "TEST is enabled")
    add_subdirectory(test)
endif ()
