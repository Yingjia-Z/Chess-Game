#include "rook.h"

Rook::Rook(Board* b) : Decorator{b} {}

int Rook::canMove(int locx, int locy, int destx, int desty) {
  // check jump
  if (locx == destx && locy == desty) {  // loc and dest are the same
    return 0;

  } else {  // loc and dest are not the same
    int xIncrement = 0;
    int yIncrement = 0;

    // x is the same
    if (locx == destx) {
      yIncrement = (desty - locy) / (std::abs(desty - locy));
      for (int i = locy + yIncrement; i != desty; i += yIncrement) {
        if (b->getPiece(locx, i) != ' ' && b->getPiece(locx, i) != '_') {
          return 0;
        }
      }

    } else if (locy == desty) {  // y is the same
      xIncrement = (destx - locx) / (std::abs(destx - locx));
      for (int i = locx + xIncrement; i != destx; i += xIncrement) {
        if (b->getPiece(i, locy) != ' ' && b->getPiece(i, locy) != '_') {
          return 0;
        }
      }

    } else {  // x,y are both different, which is wrong
      return 0;
    }
  }
  return 1;
}