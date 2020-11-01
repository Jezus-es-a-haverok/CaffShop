#include <parser.hpp>
#include <base.hpp>

int main() {
  print("Hello, makefile!\n");
  std::vector<std::byte> byteCaff;
  byteCaff.push_back(std::byte(0));
  auto ret = parse(byteCaff, false);
  if(ret[0] == std::byte(ERROR)) {
    print("Test OK!\n");
  }
  return 0;
}
