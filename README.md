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
