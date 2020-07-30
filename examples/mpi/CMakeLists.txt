set(EXAMPLE_SOURCE_FILES
        main.cpp
        model_mpi.hpp
        ../common/set_nodes.cpp
        )

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin/examples)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

add_executable(pnohs-mpi ${EXAMPLE_SOURCE_FILES})
target_link_libraries(pnohs-mpi ${PNOHS_LIB_NAME} ${PNOHS_EXTRA_LIBS})
