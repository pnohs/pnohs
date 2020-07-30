set(EXAMPLE_SOURCE_FILES
        main.cpp
        model.hpp
        )

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin/examples)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

add_executable(single-node ${EXAMPLE_SOURCE_FILES})
target_link_libraries(single-node ${PNOHS_LIB_NAME} ${PNOHS_EXTRA_LIBS})
