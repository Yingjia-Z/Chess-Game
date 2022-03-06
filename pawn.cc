#include "pawn.h"

#include <iostream>

Pawn::Pawn(Board* b) : Decorator{b} {}

int Pawn::canMove(int locx, int locy, int destx, int desty) {
  char loc = b->getPiece(locx, locy);
  char dest = b->getPiece(destx, desty);
  if (loc <= 'Z' && loc >= 'A') {  // capital letter, white, up
    // standard move
    if (locy == desty && destx == locx - 1) {  // one step up
      if (b->getPiece(destx, desty) != ' ' &&
          b->getPiece(destx, desty) != '_') {  // a piece at dest
        return 0;
      } else {
        return 1;
      }

      // capture move, additionsl 1
    } else if (std::abs(desty - locy) == 1 && destx == locx - 1) {
      if (dest <= 'z' && dest >= 'a') {  // black piece at dest
        return 1;                        // capture
      } else {
        return 0;
      }

      // 2 steps up, additional rule 2
    } else if (locy == desty && destx == locx - 2) {
      if (locx == 6) {  // at initial spot
        return 1;
      } else {
        return 0;
      }

    } else {  // neither onestep forward or one step diagonal forward or two
              // steps
      return 0;
    }

  } else if (loc <= 'z' && loc >= 'a') {  // lower case, black, down
    // standard move
    if (locy == desty && destx == locx + 1) {  // one step down
      if (b->getPiece(destx, desty) != ' ' &&
          b->getPiece(destx, desty) != '_') {  // a piece at the spot
        return 0;
      } else {
        return 1;
      }

      // capture move
    } else if (std::abs(desty - locy) == 1 &&
               destx == locx + 1) {      // one diagonal step down
      if (dest <= 'Z' && dest >= 'A') {  // white piece at the spot
        return 1;                        // capture
      } else {
        return 0;
      }

      // 2 steps down, additional rule 2
    } else if (locy == desty && destx == locx + 2) {
      if (locx == 1) {  // at initial spot
        return 1;
      } else {
        return 0;
      }

    } else {  // neither onestep forward or one step diagonal forward or two
              // steps
      return 0;
    }

  } else {  // loc is neither uppercase nor lower case
    return 0;
  }
}