#include <parser.hpp>

CAFF parse(char* caffByte, uint64_t length) {
  CAFF caff(OK);
  try {
    caff.loadFromByte(caffByte, length);
  } catch (...) {
    caff = CAFF(ERROR);
  }
  return caff;
}
