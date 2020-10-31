#include <iostream>

#include <parser.hpp>
#include <caff.hpp>


std::vector<std::byte> parse(std::vector<std::byte> caffByte) {
  CAFF* caff = new CAFF();
  //Parse
  std::vector<std::byte>* bytestream = new std::vector<std::byte>();
  //convert caff to byte
  delete caff;
  return *bytestream;
}

void print(std::string msg) {
  std::cout << msg;
}
