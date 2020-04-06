
# lin

[![Build Status](https://travis-ci.com/kkrol27/lin.svg?branch=master)](https://travis-ci.com/kkrol27/lin)

Linear algebra library solely using static memory alocation. It's been developed primarily for the [PAN](https://github.com/pathfinder-for-autonomous-navigation) mission.

The library is structured into a set of individual modules.

Most of the core functionality can be included with `#include <lin/core.hpp>`. This will bring in the basic matrix types, vector types, and simple operators - e.g. matrix/vector addition, element wise scaling, taking a transpose, frobenius norm, etc.

Additional modules are available and provide more complex functionality such as the references module (`#include <lin/references.hpp>`), generators (`#include <lin/generators.hpp>`), matrix factorizations (`#include <lin/factorizations.hpp>`), etc.

All unit tests live in `test/**` and can be run with:

    mkdir build
    cd build
    cmake ../
    cmake --build .
    ctest .
