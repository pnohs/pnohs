set(INCLUDE_FILES
        )

set(HEADER_FILES
        app.h
        )

set(SOURCE_FILES
        app.cpp
        )

set(MAIN_FILE main.cpp)

add_library(${LIB_NAME_SRC} STATIC ${INCLUDE_FILES} ${SOURCE_FILES} ${HEADER_FILES}) # libapp is also used in test.

add_executable(${PROJECT_NAME} ${MAIN_FILE})

target_link_libraries(${PROJECT_NAME} ${LIB_NAME_SRC} ${EXTRA_LIBS}) # extra lib
