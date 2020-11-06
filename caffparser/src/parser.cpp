#include <iostream>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <parser.hpp>

CAFF parse(char* caffByte, uint64_t length, bool justCheck) {
  CAFF* caff = new CAFF();
  try {
    caff->loadFromByte(caffByte, length);
  } catch (...) {
    std::cout << "Error";
  }
  return *caff;
}

PYBIND11_MODULE(libcaffparser, m) {
    m.doc() = "libcaffparser C++ library";

    m.def("parse", &parse, "CAFF parse function");

    py::class_<CAFF>(m, "CAFF")
      .def(py::init<>())
      .def("getCode", &CAFF::getCode)
      .def("getCreator", &CAFF::getCreator)
      .def("getYear", &CAFF::getYear)
      .def("getMonth", &CAFF::getMonth)
      .def("getDay", &CAFF::getDay)
      .def("getHour", &CAFF::getHour)
      .def("getMin", &CAFF::getMin)
      .def("getTags", &CAFF::getTags)
      .def("getCaptions", &CAFF::getCaptions)
      .def("getThumbnail", &CAFF::getThumbnail)
      .def("getWidth", &CAFF::getWidth)
      .def("getHeight", &CAFF::getHeight);
}
