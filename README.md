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
Install [pkg](https://github.com/genshen/pkg) version 0.2.0 first.
```bash
$ cd pnohs
$ pkg fetch
$ pkg install # install dependency
```

## Build
```bash
$ cd pnohs
$ mkdir build
$ cd build
$ cmake ../  \
 -DPNOHS_OpenMP_ENABLE_FLAG=OFF \
 -DPNOHS_MPI_ENABLE_FLAG=ON \
 -DPNOHS_TEST_BUILD_ENABLE_FLAG=ON \  # enable unit tests build.
 -DPNOHS_TEST_MPI_ENABLE_FLAG=ON
$ make
$ make install
```

## CHANGELOG.
We use [chglog](https://github.com/git-chglog/git-chglog) tool to generate CHANGELOG.md file.
Make sure you have **chglog** installed before updating CHANGELOG.md file.

## LiCENSE
Mozilla Public License Version 2.0
