# store temp file, e.g. files for IO test.
set(PNOHS_TEST_TEMP_STORAGE_PATH ${CMAKE_CURRENT_BINARY_DIR})

# configure a header file to pass some of the CMake settings to the source code
configure_file(
        "${PROJECT_SOURCE_DIR}/test/unit/test_config.h.in"
        "${PROJECT_SOURCE_DIR}/test/unit/test_config.h"
)

set(TEST_HEADER_FILES
        test_config.h
        dispatch/dispatch_json_string.h
        graph/generate_graph.hpp
        )

set(TEST_SOURCE_FILES
        app_test.cpp
        main.cpp
        model_adapter_test.cpp
        dispatch/dispatch_parse_test.cpp
        ds/base_data_list_test.cpp
        ds/param_list_test.cpp
        ds/param_meta_data_test.cpp
        graph/graph_test.cpp
        graph/graph_traversing_test.cpp
        graph/node_test.cpp
        graph_extra/api_params_test.cpp
        scheduler/longest_pickup_test.cpp
        scheduler/strategy_adapter_test.cpp
        store/store_test.cpp
        utils/sim_reduction_test.cpp
        adapter/model_register_test.cpp
        )

# set binary path and lib storage path wile compiling process.
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

add_executable(${PNOHS_UINT_TEST_NAME} ${TEST_SOURCE_FILES} ${TEST_HEADER_FILES})

## Extra linking for the project: add pnohs lib
#set(PNOHS_EXTRA_LIBS ${PNOHS_LIB_NAME} ${PNOHS_EXTRA_LIBS})

# Extra linking for the project.
if (TARGET GTest::gtest AND TARGET GTest::gtest_main)
    # googletest is added by `find_package(GTest)`
    target_link_libraries(${PNOHS_UINT_TEST_NAME}
            PRIVATE GTest::gtest GTest::gtest_main ${PNOHS_LIB_NAME} ${PNOHS_EXTRA_LIBS}
            )
else ()
    # googletest is added by `add_subdirectory`
    target_link_libraries(${PNOHS_UINT_TEST_NAME}
            PRIVATE gtest gtest_main ${PNOHS_LIB_NAME} ${PNOHS_EXTRA_LIBS}
            )
endif ()

# This is so you can do 'make test' to see all your tests run, instead of
# manually running the executable runUnitTests to see those specific tests.
add_test(NAME pnohsTests COMMAND ${PNOHS_UINT_TEST_NAME})


##########################
##### install files
##########################
install(TARGETS ${PNOHS_UINT_TEST_NAME}
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        )
