#ifndef _CHESSHELPERS_H_
#define _CHESSHELPERS_H_
#include "board.h"

class ChessHelpers {
 private:
  /* data */
 public:
  bool validPiece(char p);
  bool whitePiece(char p);
  bool blackPiece(char p);

  void switchturn(std::string &whichColour, std::string &whoseturn,
                  std::string blackPlayer, std::string whitePlayer);

  bool checkBounds(int x, int y);

  // check dest and loc for whether the piece cango
  bool canGo(char loc, char dest, bool print = true);

  // check the piece's movement rule
  bool moved(Board *myboard, char loc, char dest, int movefromx, int movefromy,
             int movetox, int movetoy, bool move = true, bool print = true);

  bool checkExitSetup(Board *myboard);  // check if the conditions are met to
                                        // exit the setup mode

  bool checkcapture(Board *myboard, int kingx, int kingy, char dest);
};

class Coordinates {
 private:
  int arrayx;
  int arrayy;
  bool exist;

 public:
  Coordinates();
  void setxy(int x, int y);
  void setexist(bool e);
  int getx();
  int gety();
  bool getexist();
};

#endif