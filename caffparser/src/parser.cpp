#include <parser.hpp>

CAFF parse(char* caffByte, uint64_t length) {
  CAFF* caff = new CAFF(OK);
  try {
    caff->loadFromByte(caffByte, length);
  } catch (...) {
    caff = new CAFF(ERROR);
  }
  return *caff;
}
