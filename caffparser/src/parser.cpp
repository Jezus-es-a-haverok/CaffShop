#include <iostream>

#include <parser.hpp>
#include <caff.hpp>


std::vector<std::byte> parse(std::vector<std::byte> caffByte, bool justCheck) {

  CAFF* caff = new CAFF();
  std::vector<std::byte> bytestream;

  try {
    caff->loadFromByte(caffByte);
    ERROR_CODE retCode = caff->getCode();
    bytestream.push_back(std::byte(retCode));

    if(!justCheck && retCode == OK) {
      caff->saveToByte(bytestream);
    }

  } catch (...) {
    bytestream.insert(bytestream.begin(), std::byte(ERROR));
  }

  delete caff;
  return bytestream;
}

void print(std::string msg) {
  std::cout << msg;
}
