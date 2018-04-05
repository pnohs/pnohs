# pnohs
pnohs is Not Only Hydrological Simulation.

[![pipeline status](https://git.gensh.me/HPCer/hydrology/pnohs/badges/master/pipeline.svg)](https://git.gensh.me/HPCer/hydrology/pnohs/commits/master)
[![coverage report](https://git.gensh.me/HPCer/hydrology/pnohs/badges/develop/coverage.svg)](https://git.gensh.me/HPCer/hydrology/pnohs/commits/develop)

## Setup
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
 -DMPI_ENABLE_FLAG=ON \
 -DTEST_ENABLE_FLAG=ON \    # enable unit tests
 -DTEST_MPI_ENABLE_FLAG=ON
$ make
$ ./bin/pnohs   # run your application, you can change it to another name in file src/CMakeLists.txt
$ ./bin/unit-test   # run unit tests if you set TEST_ENABLE_FLAG to true.
$ mpirun -n 4 ./bin/pnohs   # run application in mpi environment if you set MPI_ENABLE_FLAG to true .
$ mpirun -n 4 ./bin/unit-test   # run unit tests in mpi environment if you set TEST_ENABLE_FLAG,MPI_ENABLE_FLAG and TEST_MPI_ENABLE_FLAG to true.
```
