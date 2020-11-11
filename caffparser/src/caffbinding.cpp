#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/pytypes.h>

#include <base.hpp>
#include <parser.hpp>
#include <caff.hpp>

namespace py = pybind11;

/**
 * @file
 * Contains the binding code required for using this library in python.
 */

PYBIND11_MODULE(libcaffparser, m) {
    m.doc() = "libcaffparser C++ library";

    m.def("parse", &parse, "CAFF parse function");

    py::class_<CAFF>(m, "CAFF")
      .def(py::init<ERROR_CODE>())
      .def("saveToTGA", &CAFF::saveToTGA)
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
