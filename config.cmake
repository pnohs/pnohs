set(PNOHS_VERSION "0.1.0")

option(PNOHS_OpenMP_ENABLE_FLAG "Use OpenMP" OFF) #change this flag to OFF to disable OpenMP
option(PNOHS_MPI_ENABLE_FLAG "Use MPI library" ON) #change this flag to false to disable mpi
option(PNOHS_TEST_BUILD_ENABLE_FLAG "Enable test" ON) # enable test
option(PNOHS_TEST_MPI_ENABLE_FLAG "Enable MPI in test" ON) # enable mpi in test, its value depends on option MPI_ENABLE_FLAG.
option(PNOHS_TOOLS_BUILD_ENABLE_FLAG "Enable tools building" ON) # building tools directory.
option(PNOHS_DEBUG_ENABLE_FLAG "Enable tools building" ON) # enable debug mode building.

if (PNOHS_DEBUG_ENABLE_FLAG)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
endif ()

## architecture ralated values.
# option(ARCH_SW "Enable sunway athread" OFF) # enable sunway athread if its running on sunway system.

#############
## const ##
#############
set(PNOHS_LIB_NAME ${PROJECT_NAME}) # todo use PARENT_SCOPE to modify globle variable.
# string(TOUPPER ${PROJECT_NAME} HEAD_DEFINE_PREFIX)

# test
set(PNOHS_UINT_TEST_NAME "pnohs-unit-tests")
