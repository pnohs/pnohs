# configure a header file to pass some of the CMake settings(such as debug flag) to the source code
if (PNOHS_DEBUG_ENABLE_FLAG)
    set(PNOHS_BUILDING_DEBUG_MODE ON)
endif ()

if (PNOHS_MPI_ENABLE_FLAG)
    set(PNOHS_MPI_ENABLED ON)
endif ()

configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/building_config.in"
        "${CMAKE_CURRENT_SOURCE_DIR}/building_config.h"
)

set(HEADER_FILES
        building_config.h
        nodes_pool.h
        simulation_node.h
        sys_context.h
        adapter/model_adapter.h
        adapter/model_context.h
        adapter/model_register.h
        adapter/routing_adapter.h
        adapter/runoff_adapter.h
        adapter/type_routing.h
        dispatch/dispatch_parse.h
        dispatch/dispatch_type.h
        dispatch/node_parse.h
        dispatch/dispatch_writer.h
        ds/base_data_list.hpp
        ds/data_list_with_meta.hpp
        ds/model_params_def.h
        ds/params_list.hpp
        graph/downstream.h
        graph/downstream_node.h
        graph/node.h
        graph/graph.h
        graph/graph_traversing.h
        graph/stream_meta.h
        graph/upstream.h
        graph/upstream_node.h
        graph_extra/api_graph_meta.h
        graph_extra/api_params.h
        message/looper.h
        message/stream_routing_message_runner.h
        utils/predefine.h
        scheduler/longest_pickup.h
        scheduler/ring_pickup.h
        scheduler/s_context.h
        scheduler/scheduler.h
        scheduler/strategy_adapter.h
        scheduler/strategy_container.h
        store/store_define.h
        store/store_reader.hpp
        store/store_writer.hpp
        store/store_utils.hpp
        store/2d_store_reader.hpp
        store/2d_store_writer.hpp
        utils/stopwatch.h
        utils/sim_domain.h
        utils/sim_reduction.hpp
        )

set(SOURCE_FILES
        nodes_pool.cpp
        simulation_node.cpp
        sys_context.cpp
        adapter/model_adapter.cpp
        adapter/model_context.cpp
        adapter/model_register.cpp
        adapter/routing_adapter.cpp
        adapter/runoff_adapter.cpp
        adapter/type_routing.cpp
        dispatch/dnode.hpp
        dispatch/node_parse.cpp
        dispatch/dispatch_parse.cpp
        dispatch/dispatch_writer.cpp
        graph/downstream.cpp
        graph/downstream_node.cpp
        graph/node.cpp
        graph/graph.cpp
        graph/graph_traversing.cpp
        graph/stream_meta.cpp
        graph/upstream.cpp
        graph/upstream_node.cpp
        graph_extra/api_graph_meta.cpp
        graph_extra/api_params.cpp
        message/looper.cpp
        message/stream_routing_message_runner.cpp
        scheduler/longest_pickup.cpp
        scheduler/ring_pickup.cpp
        scheduler/s_context.cpp
        scheduler/scheduler.cpp
        scheduler/strategy_adapter.cpp
        scheduler/strategy_container.cpp
        store/store_reader.inl
        store/store_writer.inl
        store/store_wr_base.hpp
        store/2d_store_reader.inl
        store/2d_store_writer.inl
        utils/stopwatch.cpp
        utils/sim_domain.cpp
        )

# set binary path and lib storage path for compiling process.
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

# make lib
add_library(${PNOHS_LIB_NAME} STATIC ${HEADER_FILES} ${SOURCE_FILES})

target_include_directories(
        ${PNOHS_LIB_NAME}
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(
        ${PNOHS_LIB_NAME}
        PUBLIC
        kiwi::kiwi
        # fmt is included in kiwi.
)

##########################
##### install files
##########################
set(TARGETS_EXPORT_NAME ${PNOHS_LIB_NAME}-targets)
set(PNOHS_LIB_CMAKE_DIR lib/cmake/${PNOHS_LIB_NAME})
set(PNOHS_LIB_CMAKE_NAMESPACE ${PNOHS_LIB_NAME}::)
set(PNOHS_LIB_CMAKE_CONFIG_IN "${PNOHS_LIB_NAME}-config.cmake.in")
set(PNOHS_LIB_CMAKE_CONFIG_OUT "${CMAKE_CURRENT_BINARY_DIR}/${PNOHS_LIB_NAME}-config.cmake")

# lib alias to makes it possible to always use the namespace version consistently
add_library(${PNOHS_LIB_NAME}::${PNOHS_LIB_NAME} ALIAS ${PNOHS_LIB_NAME})

# install bin and libs.
install(TARGETS ${PNOHS_LIB_NAME}
        EXPORT ${TARGETS_EXPORT_NAME}
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        )

# install header.
install(DIRECTORY "./"
        DESTINATION "include"
        FILES_MATCHING
        PATTERN "*.h"
        PATTERN "*.hpp"
        PATTERN "*.inl"
        )

# install export target and config for find_package
install(EXPORT ${TARGETS_EXPORT_NAME} DESTINATION ${PNOHS_LIB_CMAKE_DIR} NAMESPACE ${PNOHS_LIB_CMAKE_NAMESPACE}) # todo
include(CMakePackageConfigHelpers)
configure_package_config_file(
        ${PNOHS_LIB_CMAKE_CONFIG_IN} ${PNOHS_LIB_CMAKE_CONFIG_OUT}
        INSTALL_DESTINATION ${PNOHS_LIB_CMAKE_DIR}
)
install(FILES ${PNOHS_LIB_CMAKE_CONFIG_OUT} DESTINATION ${PNOHS_LIB_CMAKE_DIR})
