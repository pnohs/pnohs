# include directory
include_directories(${PROJECT_SOURCE_DIR}/vendor/include)

# include kiwi framework. # todo if has lib.
include_directories(${KIWI_EXPORT_INCLUDE_PATH})

# configure a header file to pass some of the CMake settings(such as debug flag) to the source code
if (PNOHS_DEBUG_BUILD_ENABLE_FLAG)
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
        config_toml.h
        config_values.h
        building_config.h
        nodes_pool.h
        pnohs.h
        simulation.h
        simulation_node.h
        sys_context.h
        adapter/model_adapter.h
        adapter/model_context.h
        adapter/routing_adapter.h
        adapter/runoff_adapter.h
        adapter/type_routing.h
        dispatch/dispatch_parse.h
        dispatch/dispatch_type.h
        dispatch/node_parse.h
        dispatch/dispatch_writer.h
        graph/downstream.h
        graph/downstream_node.h
        graph/node.h
        graph/stream_meta.h
        graph/upstream.h
        graph/upstream_node.h
        message/looper.h
        message/stream_routing_message_runner.h
        models/interface_potential_evaporation_model.h
        models/simple_potential_evaporation_model.h
        models/models_config.h
        models/type_model_data.h
        models/simple_HBV_model.h
        utils/predefine.h
        scheduler/longest_pickup.h
        scheduler/ring_pickup.h
        scheduler/s_context.h
        scheduler/scheduler.h
        scheduler/strategy_adapter.h
        scheduler/strategy_container.h
        utils/stopwatch.h
        )

set(SOURCE_FILES
        config_toml.cpp
        config_values.cpp
        nodes_pool.cpp
        pnohs.cpp
        simulation.cpp
        simulation_node.cpp
        sys_context.cpp
        adapter/model_context.cpp
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
        graph/stream_meta.cpp
        graph/upstream.cpp
        graph/upstream_node.cpp
        message/looper.cpp
        message/stream_routing_message_runner.cpp
        models/simple_potential_evaporation_model.cpp
        models/type_model_data.cpp
        models/simple_HBV_model.cpp
        scheduler/longest_pickup.cpp
        scheduler/ring_pickup.cpp
        scheduler/s_context.cpp
        scheduler/scheduler.cpp
        scheduler/strategy_adapter.cpp
        scheduler/strategy_container.cpp
        utils/stopwatch.cpp
        )

# set binary path and lib storage path for compiling process.
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

# make lib
add_library(${PNOHS_LIB_NAME} STATIC ${HEADER_FILES} ${SOURCE_FILES})

##########################
##### install files
##########################
install(TARGETS ${PNOHS_LIB_NAME}
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        )

install(FILES ${HEADER_FILES} DESTINATION include) # todo head file
