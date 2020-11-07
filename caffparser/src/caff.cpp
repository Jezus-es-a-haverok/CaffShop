#include <iostream>
#include <fstream>

#include <caff.hpp>

CAFF::CAFF(ERROR_CODE errorCode) {
  code = errorCode;
}

std::string CAFF::getCreator() {
  return creator;
}
uint16_t CAFF::getYear() {
  return year;
}
uint8_t CAFF::getMonth() {
  return month;
}
uint8_t CAFF::getDay() {
  return day;
}
uint8_t CAFF::getHour() {
  return hour;
}
uint8_t CAFF::getMin() {
  return min;
}
std::vector<std::string> CAFF::getTags() {
  return tags;
}
std::vector<std::string> CAFF::getCaptions() {
  return captions;
}
std::vector<char> CAFF::getThumbnail() {
  return thumbnail;
}
uint64_t CAFF::getWidth() {
  return width;
}
uint64_t CAFF::getHeight() {
  return height;
}

ERROR_CODE CAFF::getCode() {
  return code;
}

/** Converts 8 byte arrays to integer. */
uint64_t toLong(char bytes[8]) {
  uint64_t result = 0;
  for(int i=0; i<8; i++) {
    uint64_t temp = uint8_t(bytes[i]);
    for(int j = 0; j<i; j++) {
      temp *= 256;
    }
    result += temp;
  }
  return result;
}

/** Reads 8 bytes and converts to integer @see toLong() */
uint64_t read8Bytes(uint64_t& index, char* caffByte) {
  char arr[8];
  for(unsigned i=0; i < 8; i++) {
    arr[i] = caffByte[index];
    index++;
  }
  return toLong(arr);
}

/** Read the ID. */
char readId(uint64_t& index, char* caffByte) {
  char Id = caffByte[index++];
  return Id;
}

/** Reads 2 bytes and converts to integer. */
int read2Bytes(uint64_t& index, char* caffByte) {
  char yearByte[2];
  yearByte[0] = caffByte[index++];
  yearByte[1] = caffByte[index++];
  return unsigned(yearByte[1])*256 + uint8_t(yearByte[0]);
}

/** Read N bytes into the provided string. */
void readNBytesToString(uint64_t& index, char* caffByte, uint64_t length, std::string& creator) {
  uint64_t start = index;
  for(;index < start + length; index++) {
    creator += caffByte[index];
  }
}

std::string CAFF::readCaption(uint64_t& index, char* caffByte, uint64_t maxLength) {
  std::string caption;
  bool endFound = false;
  while(index < maxLength) {
    char ch = caffByte[index++];
    if(ch == '\n') {
      endFound = true;
      break;
    }
    caption += ch;
  }
  if(!endFound) {
    code = ERROR_CIFF;
  }
  return caption;
}

std::vector<std::string> CAFF::readTags(uint64_t& index, char* caffByte, uint64_t maxLength) {
  std::vector<std::string> tags;
  bool endFound = false;
  std::string tag;
  while(index < maxLength) {
    endFound = false;
    char ch = caffByte[index++];
    if(ch == '\0') {
      endFound = true;
      tags.push_back(tag);
      tag.erase();
    } else {
      tag += ch;
    }
  }
  if(!endFound) {
    std::cout << cnt++ << "\n";
    code = ERROR_CIFF;
  }
  std::cout << cnt++ << "\n";
  return tags;
}

void CAFF::savePixels(uint64_t& index, char* caffByte, uint64_t picSize, uint64_t maxReadLength) {
  this->thumbnail.reserve(picSize);
  while(index < maxReadLength) {
    this->thumbnail.push_back(caffByte[index++]);
  }
}

bool CAFF::parseCiff(uint64_t& index, char* caffByte, uint64_t maxLength, bool savePic) {
  // Sanity check
  char ciffMagic[4];
  for(unsigned i=0; i < 4; i++) {
    ciffMagic[i] = caffByte[index];
    index++;
  }
  if(ciffMagic[0] != 'C' || ciffMagic[1] != 'I' ||
     ciffMagic[2] != 'F' || ciffMagic[3] != 'F') {
    this->code = ERROR_CIFF;
    return false;
  }

  // Get length information
  uint64_t headerLength = read8Bytes(index, caffByte);
  uint64_t contentLength = read8Bytes(index, caffByte);
  uint64_t width = read8Bytes(index, caffByte);
  uint64_t height = read8Bytes(index, caffByte);
  if((contentLength != width * height * 3) || (index + contentLength > maxLength) || headerLength > maxLength) {
    code = ERROR_CIFF;
    return false;
  }
  uint64_t maxHeaderLength = headerLength - 36; // Constant header fields = 36 byte
  if(maxHeaderLength > headerLength) { // protects against underflow
    code = ERROR_CIFF;
    return false;
  }
  // Get caption
  maxHeaderLength = index + maxHeaderLength - 1; // -1 is for the \0 at tags
  this->captions.push_back(readCaption(index, caffByte, maxHeaderLength));
  if(code != OK) {
    return false;
  }
  // Get tags
  maxHeaderLength++; // compensating the -1 before
  std::vector<std::string> newTags = readTags(index, caffByte, maxHeaderLength);
  if(code != OK) {
    return false;
  }
  this->tags.reserve(newTags.size());
  this->tags.insert(this->tags.end(), newTags.begin(), newTags.end());
  // Save thumbnail if requested
  if(savePic) {
    if(contentLength == 0) {
      return false;
    }
    uint64_t maxReadLength = index + contentLength;
    savePixels(index, caffByte, contentLength, maxReadLength);
    this->width = width;
    this->height = height;
    return true;
  } else {
    //We dont need this pic, but increment the indexer
    index += contentLength;
    return false;
  }
}

bool CAFF::parseOneAnimation(uint64_t& index, char* caffByte, uint64_t maxLength, bool savePic) {
  if(readId(index, caffByte) != 3) {
    code = ERROR_CAFF;
    return false;
  }
  uint64_t blockLength = read8Bytes(index, caffByte);
  if(index + blockLength > maxLength) {
    code = ERROR_CAFF;
    return false;
  }
  uint64_t duration = read8Bytes(index, caffByte);
  return parseCiff(index, caffByte, maxLength, savePic);
}

void CAFF::parseAnimations(uint64_t& index, char* caffByte, uint64_t maxLength) {
  if(this->animNum == 0) {
    return;
  }
  if(index + this->animNum * 9 > maxLength) {
    code = ERROR_CAFF;
    return;
  }
  bool savedPic = false;
  // Try to parse all animations and save one thumbnail
  for(unsigned i=0; i<this->animNum; i++) {
    if(!savedPic) {
      savedPic = parseOneAnimation(index, caffByte, maxLength, true);
    } else {
      parseOneAnimation(index, caffByte, maxLength, true);
    }
    if(code != OK) {
      return;
    }
  }
  if(!savedPic) {
    code = ERROR_CAFF;
  }
}

void CAFF::parseCredits(uint64_t& index, char* caffByte, uint64_t maxLength) {
  if(index + 23 > maxLength) {
    code = ERROR_CREDITS;
    return;
  }

  if(readId(index, caffByte) != 2) {
    code = ERROR_CREDITS;
    return;
  }

  uint64_t blockLength = read8Bytes(index, caffByte);
  if(index + blockLength > maxLength) {
    code = ERROR_CREDITS;
    return;
  }
  //Get creation time
  this->year = read2Bytes(index, caffByte);
  this->month = caffByte[index++];
  this->day = caffByte[index++];
  this->hour = caffByte[index++];
  this->min = caffByte[index++];
  //Get creator
  uint64_t creatorLength = read8Bytes(index, caffByte);
  if(((index + creatorLength) > maxLength) || ((blockLength-14) != creatorLength)) {
    code = ERROR_CREDITS;
    return;
  }
  readNBytesToString(index, caffByte, creatorLength, this->creator);
}

void CAFF::parseHeader(uint64_t& index, char* caffByte, uint64_t maxLength) {
  if(maxLength < 29) {
    this->code = ERROR_HEADER;
    return;
  }
  if(readId(index, caffByte) != 1) {
    this->code = ERROR_HEADER;
    return;
  }
  uint64_t headerLength = read8Bytes(index, caffByte);
  if(headerLength != 20) {
    this->code = ERROR_HEADER;
    return;
  }
  char caffMagic[4];
  for(unsigned i=0; i < 4; i++) {
    caffMagic[i] = caffByte[index];
    index++;
  }
  if(caffMagic[0] != 'C' || caffMagic[1] != 'A' ||
     caffMagic[2] != 'F' || caffMagic[3] != 'F') {
    this->code = ERROR_HEADER;
    return;
  }
  uint64_t caffHeaderLength = read8Bytes(index, caffByte);
  if(caffHeaderLength != 20) {
    this->code = ERROR_HEADER;
    return;
  }
  this->animNum = read8Bytes(index, caffByte);
}

void CAFF::loadFromByte(char* caffByte, uint64_t length) {
  uint64_t index = 0;
  parseHeader(index, caffByte, length);
  if(code == OK) {
    parseCredits(index, caffByte, length);
  }
  if(code == OK) {
    parseAnimations(index, caffByte, length);
  }
}

void CAFF::saveToFile(std::string filename) {
  static unsigned char tga[18];
  tga[2] = 2;
  tga[12] = 255 & width;
  tga[13] = 255 & (width >> 8);
  tga[14] = 255 & height;
  tga[15] = 255 & (height >> 8);
  tga[16] = 24;
  tga[17] = 32;
  std::ofstream myfile;
  myfile.open (filename);
  for(int i=0; i<18; i++) {
    myfile << tga[i];
  }
  for(int i=0; i<thumbnail.size(); i++) {
    myfile << thumbnail[i];
  }
  myfile.close();
}
