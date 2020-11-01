#ifndef FILE_CAFF_HPP
#define FILE_CAFF_HPP

#include <string>
#include <vector>
#include <map>

#include <base.hpp>


class CAFF {

public:

  CAFF();
  void loadFromByte(std::vector<std::byte>& caffByte);
  void saveToByte(std::vector<std::byte>& bytestream);
  ERROR_CODE getCode();

private:

  std::map<int, Size> size;       /* CIFF ID -> CIFF height and width */
  std::vector<std::string> tags;  /* The tags from the CIFFs */
  std::vector<Pixel> thumbnail;   /* The generated thumbnail */
  std::string Creator;            /* Creator */

  ERROR_CODE code;

};

#endif /* FILE_CAFF_HPP */
