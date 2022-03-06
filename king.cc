#include "king.h"

#include <iostream>

#include "chesshelpers.h"

King::King(Board* b) : Decorator{b} {}

int King::canMove(int locx, int locy, int destx, int desty) {
  // checking whether there is a piece at loc or dest, and out of bounds should
  // be checked before this

  // no need to check jump

  // castling, shoulld check whether king and rook have moved before this
  if (std::abs(locy - desty) == 2 && std::abs(locx - destx) == 0) {
    ChessHelpers myhelpers;
    int rooklocx = locx;
    int rookdestx = rooklocx;
    int rooklocy = 0;
    if (desty > locy) {
      rooklocy = 9;
    } else {
      rooklocy = 2;
    }
    int rookdesty = (locy + desty) / 2;

    char rookloc = b->getPiece(rooklocx, rooklocy);
    char rookdest = b->getPiece(rookdestx, rookdesty);
    if (myhelpers.checkBounds(rookdestx, rookdesty)) {
      if (rookdest == ' ' || rookdest == '_') {  // nothing at rookdest
        if (myhelpers.moved(b, rookloc, rookdest, rooklocx, rooklocy, rookdestx,
                            rookdesty)) {
          std::cout << "--King castling--" << std::endl;
          return 1;
        }
      }
    }

  } else if (std::abs(locx - destx) == 1 || std::abs(locx - destx) == 0) {
    if (std::abs(locy - desty) == 1 || std::abs(locy - desty) == 0) {
      return 1;  // can move
    }
  }
  return 0;  // cannot move
}