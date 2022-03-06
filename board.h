#ifndef _BOARD_H_
#define _BOARD_H_
#include <iostream>

class Board {
 private:
  char myboard[10][10];

 public:
  void setPiece(char piece, int x, int y);
  void setEmpty(int x, int y);
  char getPiece(int x, int y);
  void emptyBoard();
  void initialBoard();
  void printBoard();
};

#endif