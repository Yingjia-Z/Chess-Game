#include "bishop.h"

#include <cmath>

Bishop::Bishop(Board* b) : Decorator{b} {}

int Bishop::canMove(int locx, int locy, int destx, int desty) {
    // checking whether there is a piece at loc or dest, and out of bounds should
  // be checked before this
  if (std::abs(locx - destx) == std::abs(locy - desty)) {  // check diagonality
    int xIncrement = (destx - locx) / (std::abs(destx - locx));
    int yIncrement = (desty - locy) / (std::abs(desty - locy));

    for (int i = 1; i < std::abs(destx - locx); i++) {
      if (b->getPiece(locx + xIncrement * i, locy + yIncrement * i) != ' ' &&
          b->getPiece(locx + xIncrement * i, locy + yIncrement * i) != '_') {
        return 0;
      }
    }
  } else {
    return 0;
  }

  return 1;
}
