#include "chesshelpers.h"

#include <iostream>

#include "bishop.h"
#include "board.h"
#include "chesshelpers.h"
#include "king.h"
#include "knight.h"
#include "noPieces.h"
#include "pawn.h"
#include "queen.h"
#include "rook.h"
class computer;

bool blackPieces(char p) {
  if (p == 'k' || p == 'q' || p == 'b' || p == 'r' || p == 'n' || p == 'p') {
    return true;
  } else {
    return false;
  }
}

bool whitePieces(char p) {
  if (p == 'K' || p == 'Q' || p == 'B' || p == 'R' || p == 'N' || p == 'P') {
    return true;
  } else {
    return false;
  }
}

// check if a character p is a valid piece or not
bool ChessHelpers::validPiece(char p) {
  if (p == 'K' || p == 'k' || p == 'Q' || p == 'q' || p == 'B' || p == 'b' ||
      p == 'R' || p == 'r' || p == 'N' || p == 'n' || p == 'P' || p == 'p') {
    return true;
  } else {
    return false;
  }
}

bool ChessHelpers::whitePiece(char p) {
  if (p == 'K' || p == 'Q' || p == 'B' || p == 'R' || p == 'N' || p == 'P') {
    return true;
  } else {
    return false;
  }
}

bool ChessHelpers::blackPiece(char p) {
  if (p == 'k' || p == 'q' || p == 'b' || p == 'r' || p == 'n' || p == 'p') {
    return true;
  } else {
    return false;
  }
}

void ChessHelpers::switchturn(std::string &whichColour, std::string &whoseturn,
                              std::string blackPlayer,
                              std::string whitePlayer) {
  if (whichColour == "white") {
    whichColour = "black";
  } else if (whichColour == "black") {
    whichColour = "white";
  }
  if (whoseturn == blackPlayer) {
    whoseturn = whitePlayer;
  } else if (whoseturn == whitePlayer) {
    whoseturn = blackPlayer;
  }
}

bool ChessHelpers::checkBounds(int x, int y) {
  if (x < 0 || x > 7 || y < 2 || y > 9) {
    return false;
  } else {
    return true;
  }
}

bool ChessHelpers::canGo(char loc, char dest, bool print) {
  if (loc == ' ' || loc == '_') {  // no piece at loc
    if (print)
      std::cout << "--You cannot move an empty square, please input again--"
                << std::endl;
    return false;

  } else if (dest != ' ' && dest != '_') {  // a piece at loc, a piece at dest
    // check if loc and dest are of the same camp
    if ((loc >= 'a' && loc <= 'z' && dest >= 'a' && dest <= 'z') ||
        (loc >= 'A' && loc <= 'Z' && dest >= 'A' &&
         dest <= 'Z')) {  // of the same camp
      if (print)
        std::cout
            << "--You cannot capture your own pieces, please input again--"
            << std::endl;
      return false;
    } else {  // of different colour
      // capture;
      return true;
    }

  } else {  // a piece at loc, no piece at dest
    return true;
  }
}

bool ChessHelpers::moved(Board *myboard, char loc, char dest, int movefromx,
                         int movefromy, int movetox, int movetoy, bool move,
                         bool print) {
  int moved = 0;
  Pieces *mypieces = new NoPieces;

  if (loc == 'K' || loc == 'k') {
    mypieces = new King(myboard);
    moved = mypieces->canMove(movefromx, movefromy, movetox, movetoy);
  } else if (loc == 'Q' || loc == 'q') {
    mypieces = new Queen(myboard);
    moved = mypieces->canMove(movefromx, movefromy, movetox, movetoy);
  } else if (loc == 'B' || loc == 'b') {
    mypieces = new Bishop(myboard);
    moved = mypieces->canMove(movefromx, movefromy, movetox, movetoy);
  } else if (loc == 'R' || loc == 'r') {
    mypieces = new Rook(myboard);
    moved = mypieces->canMove(movefromx, movefromy, movetox, movetoy);
  } else if (loc == 'N' || loc == 'n') {
    mypieces = new Knight(myboard);
    moved = mypieces->canMove(movefromx, movefromy, movetox, movetoy);
  } else if (loc == 'P') {
    mypieces = new Pawn(myboard);
    moved = mypieces->canMove(movefromx, movefromy, movetox, movetoy);

  } else if (loc == 'p') {
    mypieces = new Pawn(myboard);
    moved = mypieces->canMove(movefromx, movefromy, movetox, movetoy);

  } else {  // not a piece
    std::cout << "--Not a piece, please check the board--" << std::endl;
    return false;  // break?
  }
  if (moved != 0) {
    if (move) {
      myboard->setPiece(loc, movetox, movetoy);
      myboard->setEmpty(movefromx, movefromy);
    }
    if (print) {
      myboard->printBoard();
    }
    return true;
  } else {
    return false;
  }
  delete mypieces;
}

bool ChessHelpers::checkExitSetup(Board *myboard) {
  bool Kexist = false;
  bool kexist = false;
  for (int i = 0; i <= 9; i++) {
    for (int j = 0; j <= 9; j++) {
      // check if there are more than one white king
      if (myboard->getPiece(i, j) == 'K') {
        if (Kexist) {
          std::cout
              << "--More than one white king exists, cannot exit setup mode--"
              << std::endl;
          return false;
        } else {
          Kexist = true;
        }
      }
      // check if there are more than one black king
      if (myboard->getPiece(i, j) == 'k') {
        if (kexist) {
          std::cout
              << "--More than one black king exists, cannot exit setup mode--"
              << std::endl;
          return false;
        } else {
          kexist = true;
        }
      }
      // check if there are pawns on the first or last row
      if (i == 0) {
        if (myboard->getPiece(i, j) == 'p' || myboard->getPiece(i, j) == 'P') {
          std::cout << "--Pawns exist on the first row of the board, cannot "
                       "exit setup mode--"
                    << std::endl;
          return false;
        }
      }
      if (i == 7) {
        if (myboard->getPiece(i, j) == 'p' || myboard->getPiece(i, j) == 'P') {
          std::cout << "--Pawns exist on the last row of the board, cannot "
                       "exit setup mode--"
                    << std::endl;
          return false;
        }
      }
      // check checkmate
    }
  }
  return true;
}

bool ChessHelpers::checkcapture(Board *myboard, int kingx, int kingy,
                                char dest) {
  bool (*rightColourPtr)(char){nullptr};
  if (dest < 'Z' && dest > 'A') {
    rightColourPtr = &blackPieces;  // this is a pointer to a function, to use
                                    // it: rightColour(p)

  } else if (dest < 'z' && dest > 'a') {
    rightColourPtr = &whitePieces;
  }

  char loc = ' ';
  for (int i = 0; i <= 7; ++i) {
    for (int j = 2; j <= 9; ++j) {
      loc = myboard->getPiece(i, j);
      if (rightColourPtr(loc)) {
        if (checkBounds(i, j)) {
          if (canGo(loc, dest, false)) {
            if (moved(myboard, loc, dest, i, j, kingx, kingy, false, false)) {
              return true;
            }
          }
        }
      }
    }
  }
  return false;
}

Coordinates::Coordinates() {
  arrayx = -1;
  arrayy = -1;
  exist = false;
}

void Coordinates::setxy(int x, int y) {
  arrayx = x;
  arrayy = y;
}

void Coordinates::setexist(bool e) { exist = e; }

int Coordinates::getx() { return arrayx; }

int Coordinates::gety() { return arrayy; }

bool Coordinates::getexist() { return exist; }