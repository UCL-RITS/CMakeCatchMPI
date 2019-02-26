CMakeCatchMPI
------------------

[![Build Status](https://travis-ci.org/MattClarkson/CMakeCatchMPI.svg?branch=master)](https://travis-ci.org/MattClarkson/CMakeCatchMPI)
[![Build Status](https://ci.appveyor.com/api/projects/status/5pm89ej732c1ekf0/branch/master)](https://ci.appveyor.com/project/MattClarkson/cmakecatchmpi)


Purpose
-------

This is a demo project to demonstrate a reasonable structure for [CMake](https://cmake.org/) based projects,
that use [CTest](https://cmake.org/) to run unit tests via [Catch](https://github.com/catchorg/Catch2),
specifically demonstrating some uses of MPI.


Credits
-------

This project was developed as a teaching aid for UCL's ["Research Computing with C++"](http://rits.github-pages.ucl.ac.uk/research-computing-with-cpp/)
course developed by [Dr. James Hetherington](http://www.ucl.ac.uk/research-it-services/people/james)
and [Dr. Matt Clarkson](https://iris.ucl.ac.uk/iris/browse/profile?upi=MJCLA42).


Build Instructions
------------------

On Linux/Mac, in a terminal:

```sh
git clone https://github.com/UCL-RITS/CMakeCatchMPI
mkdir CMakeCatchMPI-Build
cd CMakeCatchMPI-Build
cmake -DCMAKE_BUILD_TYPE=Debug ../CMakeCatchMPI
make
```

On Windows, run the CMake GUI to generate Visual Studio project files, and run the build therein.

Run the 'Hello World' example from a terminal with:

```sh
mpiexec -np 2 ./bin/ccmpiHelloWorld
```

If you want to run more processes than you have CPUs, you'll need to use:

```sh
mpiexec -np 4 --map-by core:OVERSUBSCRIBE ./bin/ccmpiHelloWorld
```
