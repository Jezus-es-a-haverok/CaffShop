#include <string>
#include <vector>
#include "base.hpp"

/* Példa csak */

class CIFF {

  /* CIFF ID -> CIFF height and width */
  Size size;

  /* The tags from the CIFFs */
  std::vector<std::string> tags;

  /* Creator */
  std::string Creator;
};
