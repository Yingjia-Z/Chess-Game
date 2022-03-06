#ifndef _QUEEN_H_
#define _QUEEN_H_
#include <cmath>

#include "decorator.h"
class Pieces;

class Queen : public Decorator {
 private:
  /* data */
 public:
  Queen(Board* b);
  int canMove(int locx, int locy, int destx, int desty) override;
};

#endif