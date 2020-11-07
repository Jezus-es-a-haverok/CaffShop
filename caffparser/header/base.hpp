#ifndef FILE_BASE_HPP
#define FILE_BASE_HPP

/**
 * @file
 */

/**
 * Contains the error codes used while parsing the CAFF file.
 */
enum ERROR_CODE {
  OK,             /**< There were no errors */
  ERROR,          /**< There were some unknown error(s) */
  ERROR_HEADER,   /**< There were error(s) in parsing the header part */
  ERROR_CREDITS,  /**< There were error(s) in parsing the credits part */
  ERROR_CAFF,     /**< There were error(s) in parsing the animation part */
  ERROR_CIFF      /**< There were error(s) in parsing the CIFF part */
} ;

#endif /* FILE_BASE_HPP */
