#ifndef FILE_PARSER_HPP
#define FILE_PARSER_HPP

#include <vector>
#include <string>
#include <pybind11/stl.h>


char* parse(char* caffByte, unsigned long length, bool justCheck);

void print(std::string);

#endif /* FILE_PARSER_HPP */
