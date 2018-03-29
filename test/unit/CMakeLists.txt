
# configure a header file to pass some of the CMake settings to the source code
configure_file(
        "${PROJECT_SOURCE_DIR}/test/unit/test_config.h.in"
        "${PROJECT_SOURCE_DIR}/test/unit/test_config.h"
)

include_directories(${PROJECT_SOURCE_DIR}/vendor/include)
include_directories(${PROJECT_SOURCE_DIR}/src)
#include_directories(${PROJECT_SOURCE_DIR}/src/pre_handle)
#include_directories(${PROJECT_SOURCE_DIR}/src/pre_handle/entity)

set(TEST_HEADER_FILES
        test_config.h
        gtest_env.h
        )

set(TEST_SOURCE_FILES
        main.cpp
        app_test.cpp
        ../../../src/pre_handle/entity/info_subbasin.cpp ../../../src/pre_handle/entity/info_subbasin.h ../../../src/pre_handle/entity/geo_info_subbasin.cpp ../../../src/pre_handle/entity/geo_info_subbasin.h ../../../src/pre_handle/entity/soil_info_subbasin.cpp ../../../src/pre_handle/entity/soil_info_subbasin.h ../../../src/pre_handle/entity/force_info_subbasin.cpp ../../../src/pre_handle/entity/force_info_subbasin.h ../../../src/pre_handle/constant_subbasin_info.h ../../../src/pre_handle/constant.h ../../../src/pre_handle/read_subbasins_info.cpp ../../../src/pre_handle/read_subbasins_info.h ../../../src/pre_handle/dao_read_subbasins_info.cpp ../../../src/pre_handle/dao_read_subbasins_info.h test_read_subbasin_info.h
        )

set(pre_handle/entity/info_subbasin.cpp pre_handle/entity/info_subbasin.h pre_handle/entity/geo_info_subbasin.cpp pre_handle/entity/geo_info_subbasin.h pre_handle/entity/soil_info_subbasin.cpp pre_handle/entity/soil_info_subbasin.h pre_handle/entity/force_info_subbasin.cpp pre_handle/entity/force_info_subbasin.h pre_handle/constant_subbasin_info.h pre_handle/constant.h pre_handle/read_subbasins_info.cpp pre_handle/read_subbasins_info.h pre_handle/dao_read_subbasins_info.cpp pre_handle/dao_read_subbasins_info.h)

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
