# src directory
include_directories(${PROJECT_SOURCE_DIR}/vendor/include)

# include kiwi framework. # todo if has lib.
add_subdirectory(${PROJECT_SOURCE_DIR}/vendor/src/kiwi ${PROJECT_BINARY_DIR}/vendor/kiwi)
include_directories(${KIWI_EXPORT_INCLUDE_PATH})

set(EXTRA_LIBS ${EXTRA_LIBS} kiwi)

set(HEADER_FILES
        app.h
        )

set(SOURCE_FILES
        app.cpp
        )

set(MAIN_FILE main.cpp)

# set binary path and lib storage path for compiling process.
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

# make lib
add_library(${M_LIB_NAME} STATIC ${ARCH_FILES} ${HEADER_FILES} ${SOURCE_FILES})
set(EXTRA_LIBS ${EXTRA_LIBS} ${M_LIB_NAME})

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
