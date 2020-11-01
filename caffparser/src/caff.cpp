#include <iostream>

#include <caff.hpp>


CAFF::CAFF() {
  code = ERROR;
}

void CAFF::loadFromByte(std::vector<std::byte>& caffByte) {
  std::cout << "loadFromByte not implemented yet!";
}
void CAFF::saveToByte(std::vector<std::byte>& bytestream) {
  std::cout << "saveToByte not implemented yet!";
}
ERROR_CODE CAFF::getCode() {
  return code;
}
