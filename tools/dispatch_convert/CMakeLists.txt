set(HEADER_FILES
        convert.h
        )

set(SOURCE_FILES
        main.cpp
        convert.cpp
        )

# set binary path and lib storage path for compiling process.
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

add_executable(disc ${SOURCE_FILES} ${HEADER_FILES})

# Extra linking for the binary.
target_link_libraries(disc
        PRIVATE ${PNOHS_EXTRA_LIBS} ${PNOHS_LIB_NAME}
        )

##########################
##### install files
##########################
install(TARGETS disc
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        )

#install(FILES ${HEADER_FILES} DESTINATION include) # todo head file