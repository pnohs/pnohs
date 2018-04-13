cmake_minimum_required(VERSION 3.8)
include(config.cmake)

project(${AppName})

set(CMAKE_CXX_STANDARD 11)

include(dependency.cmake)

add_subdirectory(src)

###### tools
if (TOOLS_BUILD_ENABLE_FLAG)
    add_subdirectory(tools)
endif ()

################################
## test configure
################################
if (TEST_BUILD_ENABLE_FLAG)
    MESSAGE(STATUS "TEST is enabled")
    add_subdirectory(test)
endif ()