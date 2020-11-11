#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

#include <parser.hpp>
#include <base.hpp>

int main(int argc, char *argv[] ) {
  if(argc != 2) {
    std::cout << "Rossz argument!\n";
    return 0;
  }
  std::ifstream in(argv[1]);
  std::string contents((std::istreambuf_iterator<char>(in)),
    std::istreambuf_iterator<char>());
  int length = contents.size();
  if(length > 0) {
    CAFF caff = parse((char*)contents.c_str(), length);
    if(caff.getCode() == OK) {
      caff.saveToTGA("cpptga.tga");
    }
  }
  in.close();
  //delete caff;
  return 0;
}
