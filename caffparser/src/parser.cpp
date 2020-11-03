#include <iostream>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <parser.hpp>
#include <caff.hpp>


char* parse(char* caffByte, unsigned long length, bool justCheck) {
  std::cout << "1";
  CAFF* caff = new CAFF();
  std::vector<std::byte> bytestream;
  std::cout << "2";
  try {
    std::cout << "Called parse";
    caff->loadFromByte(caffByte, length);
    ERROR_CODE retCode = caff->getCode();
    bytestream.push_back(std::byte(retCode));

    if(!justCheck && retCode == OK) {
      caff->saveToByte(bytestream);
    }

  } catch (...) {
    bytestream.insert(bytestream.begin(), std::byte(ERROR));
    std::cout << "Error";
  }

  delete caff;
  char* ret = "asd";
  return ret;
}

void print2(std::string msg) {
  std::cout << msg;
}

PYBIND11_MODULE(libcaffparser, m) {
    m.doc() = "libcaffparser C++ library";

    m.def("parse", &parse, "CAFF parse function");
    //m.def("print2", &print2, "sample print");

    //py::class_<Pet>(m, "CAFF")
    //    .def(py::init<>());
        //.def("setName", &Pet::setName)
      //  .def("getName", &Pet::getName);
}
