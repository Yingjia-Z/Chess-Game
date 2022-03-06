#ifndef _KING_H_
#define _KING_H_
#include <cmath>

#include "decorator.h"
class Pieces;

class King : public Decorator {
 private:
  /* data */
 public:
  King(Board* b);
  int canMove(int locx, int locy, int destx, int desty) override;
};

#endif