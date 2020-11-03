#include <iostream>

#include <caff.hpp>


CAFF::CAFF() {
  code = OK;
}


long long toLong(char bytes[8]) {
  long long result = 0;
  for(int i=0; i<8; i++)
  return *point;
}

long long read8Bytes(int& index, char* caffByte) {
  char arr[8];
  for(int i=0; i < 8; i++) {
    arr[i] = caffByte[index];
    index++;
  }
  return toLong(arr);
}


void CAFF::parseHeader(int& index, char* caffByte, int maxLength) {
  if(maxLength < 29) {
    this->code = ERROR;
    return;
  }
  char Id = caffByte[index];
  index++;
  if(Id != 1) {
    this->code = ERROR;
    //Throw exception?
    return;
  }

  this->headerLength = read8Bytes(index, caffByte);
  if(this->headerLength != 29) {
    this->code = ERROR;
    return;
  }

  char caffMagic[4];
  for(int i=0; i < 4; i++) {
    caffMagic[i] = caffByte[index];
    index++;
  }
  if(caffMagic[0] != 'C' || caffMagic[1] != 'A' ||
     caffMagic[2] != 'F' || caffMagic[3] != 'F') {
    this->code = ERROR;
    return;
  }

  this->caffHeaderLength = read8Bytes(index, caffByte);
  if(this->caffHeaderLength != 20) {
    this->code = ERROR;
    return;
  }

  this->animNum = read8Bytes(index, caffByte);
}

void CAFF::loadFromByte(char* caffByte, unsigned long length) {
  std::cout << "loadFromByte under construction!";
  int index = 0;
  parseHeader(index, caffByte, length);
  std::cout<<"\nHeader length " << headerLength;
  std::cout<<"\ncaff header length " << caffHeaderLength;
  std::cout<<"\nanim num " << animNum << "\n";
}

void CAFF::saveToByte(std::vector<std::byte>& bytestream) {
  std::cout << "saveToByte not implemented yet!";
}
ERROR_CODE CAFF::getCode() {
  return code;
}
