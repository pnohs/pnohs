# pnohs
pnohs is Not Only Hydrological Simulation.

[![pipeline status](https://git.gensh.me/HPCer/hydrology/pnohs/badges/master/pipeline.svg)](https://git.gensh.me/HPCer/hydrology/pnohs/commits/master)
[![coverage report](https://git.gensh.me/HPCer/hydrology/pnohs/badges/develop/coverage.svg)](https://git.gensh.me/HPCer/hydrology/pnohs/commits/develop)

## Dependency and Supported Compilers
- cmake
- c++11 supported compilers.  
  Currently, the following compilers are known to work:
  - GCC 4.9 - 7.2 (and possibly later) (gcc 4.8 can also be available if you don't compile [tools](tools) and [test](test) directory)
  - Clang 3.4 - 6.0 (and possibly later)
  - Intel C++ Compiler 17.0.2 (and possibly later)
  - Microsoft Visual C++ 2015 / Build Tools 14.0.25123.0 (and possibly later)
  - Microsoft Visual C++ 2017 / Build Tools 15.5.180.51428 (and possibly later)  
  I would be happy to learn about other compilers/versions.
- MPI
- pthread

## Install Dependency
```bash
$ cd pnohs
$ pkg install # install dependency
```

## Build
### Normal build
```bash
$ cd pnohs
$ mkdir build
$ cd build
$ cmake ../  \
 -DOpenMP_ENABLE_FLAG=OFF \
 -DMPI_ENABLE_FLAG=ON \
 -DTEST_BUILD_ENABLE_FLAG=ON \    # enable unit tests build.
 -DTEST_MPI_ENABLE_FLAG=ON \
 -DTOOLS_BUILD_ENABLE_FLAG=ON     # enable tools build.
$ make
$ ./bin/pnohs   # run your application, you can change it to another name in file src/CMakeLists.txt
$ ./bin/unit-test   # run unit tests if you set TEST_ENABLE_FLAG to true.
$ mpirun -n 4 ./bin/pnohs   # run application in mpi environment if you set MPI_ENABLE_FLAG to true .
$ mpirun -n 4 ./bin/unit-test   # run unit tests in mpi environment if you set TEST_ENABLE_FLAG,MPI_ENABLE_FLAG and TEST_MPI_ENABLE_FLAG to true.
```

### Build static binary.
From [wikipedia](https://en.wikipedia.org/wiki/Static_library)
> The most significant of static building is that the application can be certain that
all its libraries are present and that they are the correct version.  
Static linking can also allow the application to be contained in a single executable file, simplifying distribution and installation.

Currently, to perform static build, you must modify cmake script files.

- in [config.cmake](config.cmake) file:

```diff
#############
## options ##
#############
# change to mpicc and mpicxx
-#set(CMAKE_C_COMPILER mpicc -cc=gcc -cxx=g++)
-#set(CMAKE_CXX_COMPILER mpicxx -cc=gcc -cxx=g++)
+set(CMAKE_C_COMPILER mpicc)
+set(CMAKE_CXX_COMPILER mpicxx)
```

- in [dependency.cmake](dependency.cmake) file:

```diff
if (MPI_ENABLE_FLAG)
    find_package(MPI REQUIRED)
    MESSAGE(STATUS "MPI_INCLUDE dir:" ${MPI_INCLUDE_PATH})
    MESSAGE(STATUS "MPI_LIBRARIES dir:" ${MPI_LIBRARIES})

    if (MPI_CXX_COMPILE_FLAGS)
-        set(COMPILE_FLAGS "${COMPILE_FLAGS} -${MPI_CXX_COMPILE_FLAGS}")
+        set(COMPILE_FLAGS "${COMPILE_FLAGS} -static_mpi ${MPI_CXX_COMPILE_FLAGS}")
    endif ()

    if (MPI_CXX_LINK_FLAGS)
        set(LINK_FLAGS "${LINK_FLAGS} ${MPI_CXX_LINK_FLAGS}")
    endif ()

    include_directories(${MPI_CXX_INCLUDE_PATH})

-#    set(EXTRA_LIBS ${EXTRA_LIBS} ${MPI_CXX_LIBRARIES}) #add mpi lib
endif ()
```

- in [src/CMakeLists.txt](src/CMakeLists.txt) file:

```diff
add_library(${M_LIB_NAME} STATIC ${HEADER_FILES} ${SOURCE_FILES})
set(EXTRA_LIBS ${M_LIB_NAME} ${EXTRA_LIBS})

add_executable(${M_EXECUTE_BIN_NAME} ${MAIN_FILE})

+ set_target_properties(${M_EXECUTE_BIN_NAME} PROPERTIES LINK_FLAGS "-static -static-libgcc -static-libstdc++")
target_link_libraries(${M_EXECUTE_BIN_NAME} ${EXTRA_LIBS}) # extra lib
```

