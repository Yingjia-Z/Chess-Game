#include "queen.h"

#include <cmath>

Queen::Queen(Board* b) : Decorator{b} {}

int Queen::canMove(int locx, int locy, int destx, int desty) {
  // checking whether there is a piece at loc or dest, and out of bounds should
  // be checked before this

  // checking jump
  if (locx == destx && locy == desty) {  // dest and loc are the same
    return 0;

  } else {  // loc is different from dest
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

    } else {  // x and y are both not same
      xIncrement = (destx - locx) / (std::abs(destx - locx));
      yIncrement = (desty - locy) / (std::abs(desty - locy));
      if (std::abs(locx - destx) ==
          std::abs(locy - desty)) {  // is a diagnal path

        for (int i = 1; i < std::abs(destx - locx); i++) {
          std::cout << b->getPiece(locx + xIncrement * i, locy + yIncrement * i)
                    << std::endl;
          if (b->getPiece(locx + xIncrement * i, locy + yIncrement * i) !=
                  ' ' &&
              b->getPiece(locx + xIncrement * i, locy + yIncrement * i) !=
                  '_') {
            return 0;
          }
        }

      } else {
        return 0;
      }
    }
  }

  return 1;  // canMove
}
