#ifndef _ROOK_H_
#define _ROOK_H_
#include <cmath>

#include "decorator.h"
class Pieces;

class Rook : public Decorator {
 private:
  /* data */
 public:
  Rook(Board* b);
  int canMove(int locx, int locy, int destx, int desty) override;
};

#endif