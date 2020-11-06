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
      .def("saveToFile", &CAFF::saveToFile)
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

    py::enum_<ERROR_CODE>(m, "ERROR_CODE")
      .value("OK", ERROR_CODE::OK)
      .value("ERROR", ERROR_CODE::ERROR)
      .value("ERROR_HEADER", ERROR_CODE::ERROR_HEADER)
      .value("ERROR_CREDITS", ERROR_CODE::ERROR_CREDITS)
      .value("ERROR_CAFF", ERROR_CODE::ERROR_CAFF)
      .value("ERROR_CIFF", ERROR_CODE::ERROR_CIFF)
      .export_values();
}
