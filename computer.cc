#include "computer.h"

#include <iostream>

#include "chesshelpers.h"

std::string colour(char p) {
  if (p == 'k' || p == 'q' || p == 'b' || p == 'r' || p == 'n' || p == 'p') {
    return "black";
  } else if (p == 'K' || p == 'Q' || p == 'B' || p == 'R' || p == 'N' ||
             p == 'P') {
    return "white";
  } else {
    return "wrong";
  }
}

bool blackPiece(char p) {
  if (p == 'k' || p == 'q' || p == 'b' || p == 'r' || p == 'n' || p == 'p') {
    return true;
  } else {
    return false;
  }
}

bool whitePiece(char p) {
  if (p == 'K' || p == 'Q' || p == 'B' || p == 'R' || p == 'N' || p == 'P') {
    return true;
  } else {
    return false;
  }
}

Computer::Computer(Board *b) : myboard(b) {}

Computer::~Computer() { delete myboard; }

void Computer::computer1(std::string whichColour) {
  bool (*rightColourPtr)(char){nullptr};
  if (whichColour == "white") {
    rightColourPtr = &whitePiece;  // this is a pointer to a function, to use
                                   // it: rightColour(p)

  } else if (whichColour == "black") {
    rightColourPtr = &blackPiece;
  }

  int arrayx = rand() % 8;      // 0~7
  int arrayy = rand() % 8 + 2;  // 2~9
  char pick = myboard->getPiece(arrayx, arrayy);

  // randomly find a piece
  bool rightColour = rightColourPtr(pick);
  while (!rightColour) {  // remember to delete "|| (pick != 'k')"
    arrayx = rand() % 8;
    arrayy = rand() % 10 + 2;
    pick = myboard->getPiece(arrayx, arrayy);
    rightColour = rightColourPtr(pick);
  }

  int movetox = -1;
  int movetoy = -1;

  autoMove1(myboard, pick, arrayx, arrayy, movetox, movetoy);
}

void Computer::computer2(std::string whichColour) {}

char randomPiece(char pawn) {
  int a = rand() % 4;  // 0~3
  if (pawn == 'p') {
    if (a == 0) {
      return 'r';
    } else if (a == 1) {
      return 'n';
    } else if (a == 2) {
      return 'b';
    } else {
      return 'q';
    }
  } else {
    if (a == 0) {
      return 'R';
    } else if (a == 1) {
      return 'N';
    } else if (a == 2) {
      return 'B';
    } else {
      return 'Q';
    }
  }
}

void checkpawn(Board *myboard, char loc, int movefromx, int movefromy,
               int movetox, int movetoy) {
  if (loc == 'p' && movetox == 7) {
    char loc2 = randomPiece(loc);
    myboard->setPiece(loc2, movetox, movetoy);
    myboard->printBoard();
    std::cout << "--computer reached the other end, replacing p with " << loc2
              << "--" << std::endl;
  } else if (loc == 'P' && movetox == 0) {
    char loc2 = randomPiece(loc);
    myboard->setPiece(loc2, movetox, movetoy);
    myboard->printBoard();
    std::cout << "--computer reached the other end, replacing P with " << loc2
              << "--" << std::endl;
  }
}

void Computer::autoMove1(Board *myboard, char loc, int movefromx, int movefromy,
                         int movetox, int movetoy, bool print) {
  ChessHelpers myhelpers;
  int count = 0;
  int possiblex = rand() % 8;
  int possibley = rand() % 10 + 2;
  char dest = myboard->getPiece(possiblex, possibley);

  while (true && count <= 640) {
    ++count;
    if (!(possiblex == movefromx && possibley == movefromy)) {
      if (myhelpers.checkBounds(possiblex, possibley)) {
        if (myhelpers.canGo(loc, dest, false)) {
          movetox = possiblex;
          movetoy = possibley;
          if (print) {
            if (myhelpers.moved(myboard, loc, dest, movefromx, movefromy,
                                movetox, movetoy)) {
              if (loc == 'p' || loc == 'P')
                checkpawn(myboard, loc, movefromx, movefromy, movetox, movetoy);
              break;
            }
          } else {
            if (myhelpers.moved(myboard, loc, dest, movefromx, movefromy,
                                movetox, movetoy, true, false)) {
              if (loc == 'p' || loc == 'P')
                checkpawn(myboard, loc, movefromx, movefromy, movetox, movetoy);
              break;
            }
          }
        }
      }
    }

    possiblex = rand() % 8;
    possibley = rand() % 10 + 2;
  }

  if (count > 640) {
    computer1(colour(loc));
  }
}