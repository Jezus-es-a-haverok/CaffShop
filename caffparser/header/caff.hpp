#ifndef FILE_CAFF_HPP
#define FILE_CAFF_HPP

#include <string>
#include <vector>
#include <map>
#include <pybind11/pytypes.h>

#include <base.hpp>

namespace py = pybind11;


class CAFF {

public:

  CAFF();
  void loadFromByte(char* caffByte, unsigned long length);
  void saveToByte(std::vector<std::byte>& bytestream);
  ERROR_CODE getCode();
  std::string getCreator();

private:

  std::map<int, Size> size;         /* CIFF ID -> CIFF height and width */
  std::vector<std::string> tags;    /* The tags from the CIFFs */
  std::vector<std::string> captions;/* The captions from the CIFFS */
  std::vector<char> thumbnail;      /* The generated thumbnail */
  unsigned long long width;         /* Width of thumbnail */
  unsigned long long height;        /* Height of thumbnail */
  std::string creator;              /* Creator */


  long long headerLength;
  long long caffHeaderLength;
  long long animNum;
  int year;
  char month;
  char day;
  char hour;
  char min;
  ERROR_CODE code;


  void parseHeader(int& index, char* caffByte, int maxLength);
  void parseCredits(int& index, char* caffByte, int maxLength);
  void parseAnimations(int& index, char* caffByte, int maxLength);
  bool parseOneAnimation(int& index, char* caffByte, int maxLength, bool savePic);
  bool parseCiff(int& index, char* caffByte, int maxLength, bool savePic);
  std::string readCaption(int& index, char* caffByte, int maxLength);
  std::vector<std::string> readTags(int& index, char* caffByte, int maxLength);
  void savePixels(int& index, char* caffByte, unsigned long long picSize, unsigned long long maxReadLength);
};

#endif /* FILE_CAFF_HPP */
