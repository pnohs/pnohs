cmake_minimum_required(VERSION 3.8)
include(config.cmake)

project(${AppName})

set(CMAKE_CXX_STANDARD 11)


################################
# MPI and OpenMP
################################
if (OpenMP_ENABLE_FLAG)
    find_package(OpenMP REQUIRED)

    if (OPENMP_FOUND)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
    endif ()
endif ()

if (MPI_ENABLE_FLAG)
    find_package(MPI REQUIRED)
    MESSAGE(STATUS "MPI_INCLUDE dir:" ${MPI_INCLUDE_PATH})
    MESSAGE(STATUS "MPI_LIBRARIES dir:" ${MPI_LIBRARIES})

    if (MPI_COMPILE_FLAGS)
        set(COMPILE_FLAGS "${COMPILE_FLAGS} ${MPI_COMPILE_FLAGS}")
    endif ()

    if (MPI_LINK_FLAGS)
        set(LINK_FLAGS "${LINK_FLAGS} ${MPI_LINK_FLAGS}")
    endif ()

    include_directories(${MPI_INCLUDE_PATH})

    set(EXTRA_LIBS ${MPI_LIBRARIES} ${EXTRA_LIBS}) #add mpi lib
endif ()
##### mpi and openmp end

add_subdirectory(src)

##############################
## test configure
##############################
if (TEST_ENABLE_FLAG)
    MESSAGE(STATUS "TEST is enabled")
    add_subdirectory(test)
endif ()