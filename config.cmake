# all variables here start with "M_"
set(M_VERSION "0.2.0")
set(AppName pnohs)

#############
## options ##
#############
# change to mpicc and mpicxx
#set(CMAKE_C_COMPILER mpicc -cc=gcc -cxx=g++)
#set(CMAKE_CXX_COMPILER mpicxx -cc=gcc -cxx=g++)

option(OpenMP_ENABLE_FLAG "Use OpenMP" OFF) #change this flag to OFF to disable OpenMP
option(MPI_ENABLE_FLAG "Use MPI library" ON) #change this flag to false to disable mpi
option(TEST_ENABLE_FLAG "Enable test" ON) # enable test
option(TEST_MPI_ENABLE_FLAG "Enable MPI in test" ON) # enable mpi in test, its value depends on option MPI_ENABLE_FLAG.
option(TOOLS_BUILD_ENABLE_FLAG "Enable tools building" ON) # enable tools building (in tools directory) binary.(tools example: convert simulation result binary file to text file)

## architecture ralated values.
# option(ARCH_SW "Enable sunway athread" OFF) # enable sunway athread if its running on sunway system.

#############
## const ##
#############
set(M_EXECUTE_BIN_NAME ${AppName})
set(M_LIB_NAME "pnohsl") # todo use PARENT_SCOPE to modify globle variable.
# string(TOUPPER ${PROJECT_NAME} HEAD_DEFINE_PREFIX)

# test
set(M_UINT_TEST_NAME "unit-tests") # todo