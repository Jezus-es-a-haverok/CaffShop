# CaffShop

* **import**: Külső modulokat tartalmaz.
    * **pybind1**: pybind11 git almodul
* **caffparser**: C++ caffparser modul, python binding-gal.
* **lib**: Az elkészült library van itt fordítás után.

## Repository letöltése:

    git clone https://github.com/Jezus-es-a-haverok/CaffShop.git
    git submodule update --init

A pybind11 modul tesztjeinek futtatása (ehhez kell a python3-dev és cmake):

    cd import/pybind11
    mkdir build
    cd build
    cmake ..
    make check -j 4


## Parser fordítása

Lehet a project gyökérkönyvtárában és a caffparser/ könyvtársban is:

    make

vagy

    make all

Tisztítás:

    make clean

Tesztek automatikusan lefutnak az all esetén, de lehet kézzel:

    make test
