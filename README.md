# CaffShop

This repository contains the implementation of CaffShop where you can share CAFF files with others.

* **import**: Contains external modules.
    * **pybind1**: pybind11 git submodule.
    * **example**: some CAFF files.
* **caffparser**: C++ caffparser module, with python binding. Contains tests as well.
* **lib**: The compiled libraries are here.
* **Release**: The compiled software and required dependencies (for Windows).

## Repository:

    git clone https://github.com/Jezus-es-a-haverok/CaffShop.git
    git submodule update --init

To run the pybind11 module's tests (python3-dev and cmake are needed):

    cd import/pybind11
    mkdir build
    cd build
    cmake ..
    make check -j 4

## Compile caffparser

### Prerequisites

You will need git, make, gcc (and g++), python3-dev. For Windows: compilation mingw-gcc, minggw-gcc-python (and all dependencies. For Arch Linux there are AUR packages for these.). For doxygen generation: doxygen.

### Results

Compilation results can be:

* **lib/libcaffparser.cpython-38-x86_64-linux-gnu.so**: The implemented C++ library as a python module (with bindings).
* **libcaffparser.so**: C++ shared library for Linux.
* **libcaffparser.dll**: C++ shared library for Windows. It is not officially supported (use with care!).
* **caffparser/test/bin/test.out**: ELF executable file (Linux program) which is linked againt libcaffparser.so (has to be in the system library path or in the same directory as test.out). This executable can be used for AFL testing.

### Python tests

Python tests are in:

* **caffparser/test/bin/fuzztest.py**: Python fuzz testing. Requires test.out.
* **caffparser/test/python/test.py**: Simple Python sanity check. Requires only libcaffparser.cpython-38-x86_64-linux-gnu.so.

### Compile

The following make commands can be executed:

    make

or

    make default

makes the C++ python module, the C++ shared library (Linux only), the binary for afl testing and runs the sanity ckeck.

    make all

all the above plus the the Windows shared library.

    make libcaffparser

makes only the C++ Python module.

    make aflbin

makes the C++ shared library (Linux) and the binary for AFL testing.

    make win

makes the Windows C++ shared library and the C++ Python module for Windows.

    make runtest

runs the sanity check (and makes all required stuff).

    make clean

cleans the project

    initrelease

initializes the release directory (only need to run once).

    release

copies the compiled software to the release directory and zip everithing.

    make doxygen

generate the code documentation using doxygen.

## caffshop Django project

### Prerequisites
 The 'project currently requires the following python packages:
 * django-crispy-forms
 * pillow (needed to display the ImageField model attributes)
 * django-filter (responsible for filtering the objects in the ListView)
 * django-bootstrap-form (to make the ListView search form prettier)
 * numpy
 
 Each of these can be installed using pip:
 
   `pip install <package-name>`
   
