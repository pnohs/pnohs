
# configure a header file to pass some of the CMake settings to the source code
configure_file(
        "${PROJECT_SOURCE_DIR}/test/unit/test_config.h.in"
        "${PROJECT_SOURCE_DIR}/test/unit/test_config.h"
)

include_directories(${PROJECT_SOURCE_DIR}/vendor/include)
include_directories(${PROJECT_SOURCE_DIR}/src)
#include_directories(${PROJECT_SOURCE_DIR}/src/pre_handle)
#include_directories(${PROJECT_SOURCE_DIR}/src/pre_handle/base_entity)

set(TEST_HEADER_FILES
        test_config.h
        gtest_env.h
        test_read_subbasin_info.cpp
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
set(EXTRA_LIBS ${M_LIB_NAME} ${EXTRA_LIBS})
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
