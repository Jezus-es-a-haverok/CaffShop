#ifndef FILE_PARSER_HPP
#define FILE_PARSER_HPP

#include <vector>
#include <string>
#include <pybind11/stl.h>

#include <caff.hpp>

CAFF parse(char* caffByte, uint64_t length, bool justCheck);

#endif /* FILE_PARSER_HPP */
