#ifndef _PAWN_H_
#define _PAWN_H_
#include <cmath>

#include "decorator.h"
class Pieces;

class Pawn : public Decorator {
 private:
  /* data */
 public:
  Pawn(Board* b);
  int canMove(int locx, int locy, int destx, int desty) override;
};

#endif