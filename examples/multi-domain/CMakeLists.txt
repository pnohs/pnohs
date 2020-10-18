set(EXAMPLE_SOURCE_FILES
        main.cpp
        model_multi_domain.hpp
        ../common/set_nodes.cpp
        joinable_message_looper.h
        )

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin/examples)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

add_executable(multiple-domain ${EXAMPLE_SOURCE_FILES})
target_link_libraries(multiple-domain ${PNOHS_LIB_NAME} ${PNOHS_EXTRA_LIBS})
