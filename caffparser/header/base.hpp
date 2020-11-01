#ifndef FILE_BASE_HPP
#define FILE_BASE_HPP

struct Size {
  int X;
  int Y;
};

struct Pixel {
  int R;
  int G;
  int B;
  int A;
};

enum ERROR_CODE {
  OK=0, ERROR=1,
} ;

#endif /* FILE_BASE_HPP */
