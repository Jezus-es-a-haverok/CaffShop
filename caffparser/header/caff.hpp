#ifndef FILE_CAFF_HPP
#define FILE_CAFF_HPP

#include <string>
#include <vector>
#include <map>
#include <cstdint>

#include <base.hpp>

/**
 * @file
 */

/**
 * This class does the parsing of the CAFF file.
 * The loadFromByte method should be called to parse a CAFF file, the the getter
 * methods can be used to get the gathered data.
 * @see loadFromByte()
 */
class CAFF {

public:

  /** Initializes the code to the given ERROR_CODE.
   */
  CAFF(ERROR_CODE errorCode);

  /** Parses the given CAFF file.
   * This the top method of the parsing, calls parseHeader, parseCredits and
   * parseAnimations in this order. Creates the index that is used by all other
   * parsing functions to navigate the CAFF file's bytes. The index is passed
   * as reference.
   * @see parseHeader()
   * @see parseCredits()
   * @see parseAnimations()
   * @param caffByte is the whole CAFF file in memory.
   * @param length is the length of the file.
   */
  void loadFromByte(char* caffByte, uint64_t length);

  /** Saves the thumbnail as a TGA image.
   * Should be only called after a successful parase.
   * @param filename is new file's name.
   */
  void saveToTGA(std::string filename);

  ERROR_CODE getCode();
  std::string getCreator();
  uint16_t getYear();
  uint8_t getMonth();
  uint8_t getDay();
  uint8_t getHour();
  uint8_t getMin();
  std::vector<std::string> getTags();
  std::vector<std::string> getCaptions();
  std::vector<uint8_t> getThumbnail();
  uint64_t getWidth();
  uint64_t getHeight();

private:
  std::vector<std::string> tags;    /**< The tags from the CIFFs */
  std::vector<std::string> captions;/**< The captions from the CIFFS */
  std::vector<uint8_t> thumbnail;      /**< The generated thumbnail in RGB format */
  uint64_t width;                   /**< Width of thumbnail */
  uint64_t height;                  /**< Height of thumbnail */
  std::string creator;              /**< Creator */
  uint64_t animNum;                 /**< Number of animations */
  uint16_t year;                    /**< Year of creation */
  uint8_t month;                    /**< Month of creation */
  uint8_t day;                      /**< Day of creation */
  uint8_t hour;                     /**< Hour of creation */
  uint8_t min;                      /**< Minute of creation */
  ERROR_CODE code;                  /**< Error code used throughout the parsing */

  /** Parses the CAFF file's header.
   * Called at the beginning of parsing only once.
   * @param index is used to index the file.
   * @param caffByte is the whole CAFF file in memory.
   * @param maxLength is the length of the file.
   */
  void parseHeader(uint64_t& index, char* caffByte, uint64_t maxLength);

  /** Parses the CAFF file's credits part.
   * Called after the header is parsed, once.
   * @param index is used to index the file.
   * @param caffByte is the whole CAFF file in memory.
   * @param maxLength is the length of the file.
   */
  void parseCredits(uint64_t& index, char* caffByte, uint64_t maxLength);

  /** Parses the CAFF file's animation block.
   * Called after the credits are parsed, once. This method just parses the animation
   * block header. Calls parseOneAnimation.
   * @see parseOneAnimation()
   * @param index is used to index the file.
   * @param caffByte is the whole CAFF file in memory.
   * @param maxLength is the length of the file.
   */
  void parseAnimations(uint64_t& index, char* caffByte, uint64_t maxLength);

  /** Parses one CAFF animation.
   * Called as many times as many animation blocks are. Parses the block header
   * and calls parseCiff and passes the savePic parameter. The thumbnail should
   * be only saved once.
   * @see parseCiff()
   * @param index is used to index the file.
   * @param caffByte is the whole CAFF file in memory.
   * @param maxLength is the length of the file.
   * @param savePic should be true, to save the thumbnail.
   * @return true if thumbnail is saved, false otherwise.
   */
  bool parseOneAnimation(uint64_t& index, char* caffByte, uint64_t maxLength, bool savePic);

  /** Parses a CIFF block.
   * Called as many time as many CIFF are in the file. Parses the CIFF header, and
   * calls readCaption, readTags and savePixels to save the data in captions, tags
   * and thumbnail, respectively. The thumbnail should be only saved once.
   * @see readCaption()
   * @see readTags()
   * @see savePixels()
   * @param index is used to index the file.
   * @param caffByte is the whole CAFF file in memory.
   * @param maxLength is the length of the file.
   * @param savePic should be true, to save the thumbnail.
   * @return true if thumbnail is saved, false otherwise.
   */
  bool parseCiff(uint64_t& index, char* caffByte, uint64_t maxLength, bool savePic);

  /** Reads the CIFF's caption.
   * There should be only one caption per CIFF, ending with a \n, so if this character
   * is found, the caption is found.
   * @param index is used to index the file.
   * @param caffByte is the whole CAFF file in memory.
   * @param maxLength is the length of the file.
   * @return the caption (string).
   */
  std::string readCaption(uint64_t& index, char* caffByte, uint64_t maxLength);

  /** Reads the CiFF's tags.
   * Reads all of the CIFF's tags. The tags are seperated by \0 characters in the
   * file, the method extract them and puts them into a vector of strings.
   * @param index is used to index the file.
   * @param caffByte is the whole CAFF file in memory.
   * @param maxLength is the length of the file.
   * @return the vector of tags (strings).
   */
  std::vector<std::string> readTags(uint64_t& index, char* caffByte, uint64_t maxLength);

  /** Saves the pixels from a CIFF.
   * The pixels are in RGB format, each 1 byte. The method reads them and save them
   * in the thumbnail vector.
   * @param index is used to index the file.
   * @param caffByte is the whole CAFF file in memory.
   * @param picSize is the total size of the picture.
   * @param maxReadLength is the maximum index that could be read.
   */
  void savePixels(uint64_t& index, char* caffByte, uint64_t picSize, uint64_t maxReadLength);

};

#endif /* FILE_CAFF_HPP */
