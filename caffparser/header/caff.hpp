#ifndef FILE_CAFF_HPP
#define FILE_CAFF_HPP

#include <string>
#include <vector>
#include <map>

#include <base.hpp>

/* Példa csak */

class CAFF {

  /* CIFF ID -> CIFF height and width */
  std::map<int, Size> size;

  /* The tags from the CIFFs */
  std::vector<std::string> tags;

  /* The generated thumbnail */
  std::vector<Pixel> thumbnail;

  /* Creator */
  std::string Creator;
};

#endif /* FILE_CAFF_HPP */
