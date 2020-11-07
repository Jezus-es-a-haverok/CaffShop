#ifndef FILE_PARSER_HPP
#define FILE_PARSER_HPP

#include <vector>
#include <string>

/**
 * @file
 */

#include <caff.hpp>

/** Parses the given CAFF file.
 * Creates a CAFF class in the heap, calls it's parse function and returns it to
 * the caller. The CAFF class contains the gathered data, it's getter methods can
 * can be used to get them.
 * @see CAFF::parse()
 * @param caffByte is the whole CAFF file in memory.
 * @param length is the length of the file.
 * @warning Deletion of the CAFF file is the callers task!
 */
CAFF parse(char* caffByte, uint64_t length);

#endif /* FILE_PARSER_HPP */
