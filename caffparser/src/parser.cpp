#include <parser.hpp>

CAFF parse(char* caffByte, uint64_t length) {
  CAFF* caff = new CAFF();
  try {
    caff->loadFromByte(caffByte, length);
  } catch (...) {
  }
  return *caff;
}
