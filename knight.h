#ifndef _KNIGHT_H_
#define _KNIGHT_H_
#include <cmath>

#include "decorator.h"
class Pieces;

class Knight : public Decorator {
 private:
  /* data */
 public:
  Knight(Board* b);
  int canMove(int locx, int locy, int destx, int desty) override;
};

#endif