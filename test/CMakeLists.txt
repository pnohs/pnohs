enable_testing()

if (NOT (MPI_ENABLE_FLAG))
    set(TEST_MPI_ENABLE_FLAG OFF)  # if we disabled MPI_ENABLE_FLAG,we cann't also use TEST_MPI_ENABLE_FLAG.
endif ()
MESSAGE(STATUS "MPI in test: ${TEST_MPI_ENABLE_FLAG}")

add_subdirectory(unit)

# set(TEST_LIBRARY_TO_USE "catch2" CACHE STRING "test library selected at CMake configure time,googletest or catch2")
# set_property(CACHE TEST_LIBRARY_TO_USE PROPERTY STRINGS googletest catch2)
# if (${TEST_LIBRARY_TO_USE} MATCHES "googletest")
#     set(GOOGLE_TEST_ENABLE_FLAG ON)
# else ()
#     set(CATCH2_TEST_ENABLE_FLAG ON)
# endif ()
