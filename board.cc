#include "board.h"

void Board::setPiece(char piece, int x, int y) { myboard[x][y] = piece; }

void Board::setEmpty(int x, int y) {
  ((x + y) % 2 == 0) ? myboard[x][y] = ' ' : myboard[x][y] = '_';
}

char Board::getPiece(int x, int y) { return myboard[x][y]; }

void Board::emptyBoard() {
  // set the board to empty
  for (int i = 0; i <= 9; i++) {
    for (int j = 0; j <= 9; j++) {
      this->setPiece(' ', i, j);
    }
  }

  // set chess board layout
  for (int i = 0; i <= 7; i++) {
    for (int j = 2; j <= 9; j++) {
      this->setEmpty(i, j);
    }
  }
  // set the board boundries
  char numBoundray = '8';
  for (int i = 0; i <= 7; i++) {
    this->setPiece(numBoundray, i, 0);
    numBoundray--;
  }
  char charBoundray = 'a';
  for (int i = 2; i <= 9; i++) {
    this->setPiece(charBoundray, 9, i);
    charBoundray++;
  }
}

void Board::initialBoard() {
  this->emptyBoard();

  // set the pieces of black camps, pieces denoted using lowercase
  this->setPiece('r', 0, 2);
  this->setPiece('n', 0, 3);
  this->setPiece('b', 0, 4);
  this->setPiece('q', 0, 5);
  this->setPiece('k', 0, 6);
  this->setPiece('b', 0, 7);
  this->setPiece('n', 0, 8);
  this->setPiece('r', 0, 9);
  for (int i = 2; i <= 9; i++) {
    this->setPiece('p', 1, i);
  }

  // set the pieces of white camps, pieces denoted using uppercase
  this->setPiece('R', 7, 2);
  this->setPiece('N', 7, 3);
  this->setPiece('B', 7, 4);
  this->setPiece('Q', 7, 5);
  this->setPiece('K', 7, 6);
  this->setPiece('B', 7, 7);
  this->setPiece('N', 7, 8);
  this->setPiece('R', 7, 9);
  for (int i = 2; i <= 9; i++) {
    this->setPiece('P', 6, i);
  }
}

void Board::printBoard() {
  for (int i = 0; i <= 9; i++) {
    for (int j = 0; j <= 9; j++) {
      char p = getPiece(i, j);
      std::cout << p;
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}