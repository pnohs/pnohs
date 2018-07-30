################################
# MPI and OpenMP
################################
if (PNOHS_OpenMP_ENABLE_FLAG)
    find_package(OpenMP REQUIRED)

    if (OPENMP_FOUND)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
    endif ()
endif ()

if (PNOHS_MPI_ENABLE_FLAG)
    find_package(MPI REQUIRED)
    MESSAGE(STATUS "MPI_INCLUDE dir:" ${MPI_INCLUDE_PATH})
    MESSAGE(STATUS "MPI_LIBRARIES dir:" ${MPI_LIBRARIES})

    if (MPI_CXX_COMPILE_FLAGS)
        set(COMPILE_FLAGS "${COMPILE_FLAGS} ${MPI_CXX_COMPILE_FLAGS}")
    endif ()

    if (MPI_CXX_LINK_FLAGS)
        set(LINK_FLAGS "${LINK_FLAGS} ${MPI_CXX_LINK_FLAGS}")
    endif ()

    include_directories(${MPI_CXX_INCLUDE_PATH})

    set(PNOHS_EXTRA_LIBS ${PNOHS_EXTRA_LIBS} ${MPI_CXX_LIBRARIES}) #add mpi lib
endif ()
##### mpi and openmp end

################################
###### kiwi framework globally
################################
if (NOT TARGET kiwi)
    add_subdirectory(${CMAKE_SOURCE_DIR}/vendor/src/kiwi ${PROJECT_BINARY_DIR}/vendor/kiwi)
endif ()
set(PNOHS_EXTRA_LIBS ${KIWI_EXPORT_LINK_LIBS} ${PNOHS_EXTRA_LIBS})
#set(EXTRA_LIBS fmt kiwi ${EXTRA_LIBS}) # todo use KIWI_EXPORT_LIBS

################################
##### check pthread lib
################################
find_package(Threads REQUIRED)
set(PNOHS_EXTRA_LIBS ${PNOHS_EXTRA_LIBS} ${CMAKE_THREAD_LIBS_INIT})
MESSAGE(STATUS "pthread is used.")
## pthread end
