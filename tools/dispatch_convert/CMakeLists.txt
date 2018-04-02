# json dependency directory
include_directories(${PROJECT_SOURCE_DIR}/vendor/pkg/include)
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${KIWI_EXPORT_INCLUDE_PATH})

set(HEADER_FILES
        convert.h
        )

set(SOURCE_FILES
        main.cpp
        convert.cpp
        ahct.h)

# set binary path and lib storage path for compiling process.
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

add_executable(disc ${SOURCE_FILES} ${HEADER_FILES})
# Extra linking for the binary.
target_link_libraries(disc kiwi ${M_LIB_NAME})

##########################
##### install files
##########################
install(TARGETS disc
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        )

#install(FILES ${HEADER_FILES} DESTINATION include) # todo head file