#include <iostream>

#include <caff.hpp>


CAFF::CAFF() {
  code = OK;
}


long long toLong(char bytes[8]) {
  long long result = 0;
  for(int i=0; i<8; i++) {
    long long temp = u_char(bytes[i]);
    for(int j = 0; j<i; j++) {
      temp *= 256;
    }
    result += temp;
  }
  return result;
}

long long read8Bytes(int& index, char* caffByte) {
  char arr[8];
  for(int i=0; i < 8; i++) {
    arr[i] = caffByte[index];
    index++;
  }
  return toLong(arr);
}

char readId(int& index, char* caffByte) {
  char Id = caffByte[index++];
  std::cout << "Id: " << int(Id) << "\n";
  return Id;
}

void CAFF::parseHeader(int& index, char* caffByte, int maxLength) {
  if(maxLength < 29) {
    this->code = ERROR;
    return;
  }
  if(readId(index, caffByte) != 1) {
    this->code = ERROR;
    return;
  }

  this->headerLength = read8Bytes(index, caffByte);
  if(this->headerLength != 20) {
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

int read2Bytes(int& index, char* caffByte) {
  char yearByte[2];
  yearByte[0] = caffByte[index++];
  yearByte[1] = caffByte[index++];
  return unsigned(yearByte[1])*256 + u_char(yearByte[0]);
}

void readNBytesToString(int& index, char* caffByte, int length, std::string& creator) {
  int start = index;
  for(;index < start + length; index++) {
    creator += caffByte[index];
  }
}

void CAFF::parseCredits(int& index, char* caffByte, int maxLength) {
  if(index + 23 > maxLength) {
    code = ERROR;
    return;
  }

  if(readId(index, caffByte) != 2) {
    code = ERROR;
    return;
  }

  long long blockLength = read8Bytes(index, caffByte);
  std::cout << "creator block length: " << blockLength << "\n";
  if(index + blockLength > maxLength) {
    code = ERROR;
    return;
  }

  this->year = read2Bytes(index, caffByte);
  this->month = caffByte[index++];
  this->day = caffByte[index++];
  this->hour = caffByte[index++];
  this->min = caffByte[index++];

  long long creatorLength = read8Bytes(index, caffByte);
  std::cout << "creator length: " << creatorLength << "\n";
  if(((index + creatorLength) > maxLength) || ((blockLength-14) != creatorLength)) {
    code = ERROR;
    return;
  }

  readNBytesToString(index, caffByte, creatorLength, this->creator);
}

void CAFF::loadFromByte(char* caffByte, unsigned long length) {
  std::cout << "\nloadFromByte under construction!\n";
  int index = 0;
  parseHeader(index, caffByte, length);
  parseCredits(index, caffByte, length);
  if(code == ERROR) {
    std::cout << "Error in CAFF file!\n";
    return;
  }
  std::cout << "\nHeader length " << headerLength;
  std::cout << "\ncaff header length " << caffHeaderLength;
  std::cout << "\nanim num " << animNum << "\n";
  std::cout << "year: " << year << " month: " << int(month) << " day: " << int(day) << " hour: " << int(hour) << " min: " << int(min) << "\n";
  std::cout << "Creator: " << creator << "\n";
}

void CAFF::saveToByte(std::vector<std::byte>& bytestream) {
  std::cout << "saveToByte not implemented yet!";
}
ERROR_CODE CAFF::getCode() {
  return code;
}
