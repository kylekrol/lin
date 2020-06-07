
# lin

[![Build Status](https://travis-ci.com/kkrol27/lin.svg?branch=master)](https://travis-ci.com/kkrol27/lin)

Linear algebra library solely using static memory alocation. It's been developed primarily for the [PAN](https://github.com/pathfinder-for-autonomous-navigation) mission.

## Overview

The library is structured into a set of individual modules.

Most of the core functionality can be included with `#include <lin/core.hpp>`. This will bring in the basic matrix types, vector types, and simple operators - e.g. matrix/vector addition, element wise scaling, taking a transpose, frobenius norm, etc.

Additional modules are available and provide more complex functionality such as the references module (`#include <lin/references.hpp>`), generators (`#include <lin/generators.hpp>`), matrix factorizations (`#include <lin/factorizations.hpp>`), etc.

## Running Tests

All unit tests live in `test/**` and can be run with:

    mkdir build
    cd build
    cmake ../
    cmake --build .
    ctest .

## Documentation

Documentation can be built with doxygen by running:

    cd docs
    doxygen

and then opening `docs/html/index.html`. Starting at the modules page will be most helpful.

## Python Bindings

There is a small python module wrapping a few basic types from `lin` that have `double` elements. All of the core module is implemented with a handful of helpful additions. The source code for the it is generated at install time by the `setup.py` file.

The module can be installed with:

    pip install .

For running tests locally using a virtual environment may be useful:

    python -m venv venv
    source venv/bin/activate
    pip install -r requirements.txt
    pip install . -vvv
    pytest -v test_lin.py
