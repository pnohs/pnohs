# include directory
include_directories(${PROJECT_SOURCE_DIR}/vendor/pkg/include)

# include kiwi framework. # todo if has lib.
add_subdirectory(${PROJECT_SOURCE_DIR}/vendor/src/kiwi ${PROJECT_BINARY_DIR}/vendor/kiwi)
include_directories(${KIWI_EXPORT_INCLUDE_PATH})

set(EXTRA_LIBS kiwi ${EXTRA_LIBS})

set(HEADER_FILES
        config_toml.h
        context.h
        pnohs.h
        route.h
        simulation.h
        simulation_node.h
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
        pre_handle/entity/info_subbasin.h
        pre_handle/entity/geo_info_subbasin.h
        pre_handle/entity/soil_info_subbasin.h
        pre_handle/entity/force_info_subbasin.h
        pre_handle/constant.h
        pre_handle/read_subbasins_info.h
        pre_handle/dao_read_subbasins_info.h
        utils/typedef.h
        )

set(SOURCE_FILES
        config_toml.cpp
        context.cpp
        pnohs.cpp
        route.cpp
        simulation.cpp
        simulation_node.cpp
        dispatch/node.hpp
        dispatch/node_parse.cpp
        dispatch/dispatch_parse.cpp
        dispatch/dispatch_writer.cpp
        graph/downstream.cpp
        graph/downstream_node.cpp
        graph/node.cpp
        graph/stream_meta.cpp
        graph/upstream.cpp
        graph/upstream_node.cpp
        pre_handle/entity/info_subbasin.cpp
        pre_handle/dao_read_subbasins_info.cpp
        pre_handle/read_subbasins_info.cpp
        )

set(MAIN_FILE main.cpp)


# set binary path and lib storage path for compiling process.
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

# make lib
add_library(${M_LIB_NAME} STATIC ${HEADER_FILES} ${SOURCE_FILES})
set(EXTRA_LIBS ${M_LIB_NAME} ${EXTRA_LIBS})

add_executable(${M_EXECUTE_BIN_NAME} ${MAIN_FILE})

target_link_libraries(${M_EXECUTE_BIN_NAME} ${EXTRA_LIBS}) # extra lib

##########################
##### install files
##########################
install(TARGETS ${M_EXECUTE_BIN_NAME} ${M_LIB_NAME}
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        )

install(FILES ${HEADER_FILES} DESTINATION include) # todo head file
