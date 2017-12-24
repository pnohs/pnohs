# pnohs
pnohs is Not Only Hydrological Simulation.

## Get the pnohs code.
```bash

$ git clone http://git.gensh.me/HPCer/hydrology/pnohs.git

$ cd pnohs

$ wget https://raw.githubusercontent.com/CatchOrg/Catch2/master/single_include/catch.hpp -O test/external/catch2/catch.hpp # if you are using catch2 as test library. see document at https://github.com/catchorg/Catch2/blob/master/docs/tutorial.md

```

## Build
```bash
$ cd pnohs
$ mkdir build
$ cd build
$ cmake ../  \
 -DOpenMP_ENABLE_FLAG=ON \
 -DMPI_ENABLE_FLAG=ON \
 -DMPI_ENABLE_FLAG=ON \
 -DTEST_ENABLE_FLAG=ON \    # enable unit tests
 -DTEST_MPI_ENABLE_FLAG=ON \
 -DTEST_LIBRARY_TO_USE=catch2 \   # use catch2 or googletest as test library.
$ make
$ ./src/pnohs   # run your application, you can change it to another name in file src/CMakeLists.txt
$ ./test/unitTests   # run unit tests if you set TEST_ENABLE_FLAG to true.
$ mpirun -n 4 ./src/pnohs   # run application in mpi environment if you set MPI_ENABLE_FLAG to true .
$ mpirun -n 4 ./test/unitTests   # run unit tests in mpi environment if you set TEST_ENABLE_FLAG,MPI_ENABLE_FLAG and TEST_MPI_ENABLE_FLAG to true.
```
