#ifndef FILE_CAFF_HPP
#define FILE_CAFF_HPP

#include <string>
#include <vector>
#include <map>
#include <cstdint>
#include <pybind11/pytypes.h>

#include <base.hpp>

namespace py = pybind11;

class CAFF {

public:
  CAFF();
  void loadFromByte(char* caffByte, uint64_t length);
  void saveToFile(std::string filename);
  ERROR_CODE getCode();
  std::string getCreator();
  uint16_t getYear();
  uint8_t getMonth();
  uint8_t getDay();
  uint8_t getHour();
  uint8_t getMin();
  std::vector<std::string> getTags();
  std::vector<std::string> getCaptions();
  std::vector<char> getThumbnail();
  uint64_t getWidth();
  uint64_t getHeight();

private:
  std::vector<std::string> tags;    /* The tags from the CIFFs */
  std::vector<std::string> captions;/* The captions from the CIFFS */
  std::vector<char> thumbnail;      /* The generated thumbnail */
  uint64_t width;         /* Width of thumbnail */
  uint64_t height;        /* Height of thumbnail */
  std::string creator;              /* Creator */
  uint64_t animNum;
  uint16_t year;
  uint8_t month;
  uint8_t day;
  uint8_t hour;
  uint8_t min;
  ERROR_CODE code;

  void parseHeader(uint64_t& index, char* caffByte, uint64_t maxLength);
  void parseCredits(uint64_t& index, char* caffByte, uint64_t maxLength);
  void parseAnimations(uint64_t& index, char* caffByte, uint64_t maxLength);
  bool parseOneAnimation(uint64_t& index, char* caffByte, uint64_t maxLength, bool savePic);
  bool parseCiff(uint64_t& index, char* caffByte, uint64_t maxLength, bool savePic);
  std::string readCaption(uint64_t& index, char* caffByte, uint64_t maxLength);
  std::vector<std::string> readTags(uint64_t& index, char* caffByte, uint64_t maxLength);
  void savePixels(uint64_t& index, char* caffByte, uint64_t picSize, uint64_t maxReadLength);
};

#endif /* FILE_CAFF_HPP */
