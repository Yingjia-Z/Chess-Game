#include <iostream>
#include <string>

#include "bishop.h"
#include "board.h"
#include "chesshelpers.h"
#include "computer.h"
#include "king.h"
#include "knight.h"
#include "noPieces.h"
#include "pawn.h"
#include "queen.h"
#include "rook.h"

int main() {
  Board* myboard = new Board;
  ChessHelpers myhelpers;  // to store the helper functions;
  Pieces* mypieces = new NoPieces;
  Computer mycomputer{myboard};
  Coordinates wking;
  Coordinates bking;

  // whichColour is white when it is white's turn and black when it is
  // black's turn. By default, white goes first
  std::string whichColour = "white";

  // to determine human or computer player's turn
  std::string whoseturn = "none";
  std::string whitePlayer = "none";  // human or computer
  std::string blackPlayer = "none";

  // stores the score of palyers;
  int whitescore = 0;
  int blackscore = 0;

  // record the round number;
  int round = 1;
  bool firstmoved = false;

  // check if the setup mode has been entered or not
  bool setup = false;
  // check whwther ingame;
  bool ingame = false;

  // record whether king and rook moved or not
  bool wkingmoved = false;
  bool bkingmoved = false;
  bool wrook2moved = false;
  bool wrook9moved = false;
  bool brook2moved = false;
  bool brook9moved = false;

  std::string command;

  while (true) {
    if (ingame)
      std::cout << "--"
                << "Round " << round << ", " << whichColour << " " << whoseturn
                << "'s turn--" << std::endl;
    if (ingame && whoseturn == "computer1") {
      // search for king
      wking.setexist(false);
      bking.setexist(false);
      for (int i = 0; i <= 7; ++i) {
        for (int j = 2; j <= 9; ++j) {
          if (wking.getexist() && bking.getexist()) break;
          if (myboard->getPiece(i, j) == 'k') {
            bking.setxy(i, j);
            bking.setexist(true);
          } else if (myboard->getPiece(i, j) == 'K') {
            wking.setxy(i, j);
            wking.setexist(true);
          }
        }
      }
      if (wking.getexist() == false) {
        std::cout << "--white king has been captured, black wins--"
                  << std::endl;
        ingame = false;
        ++blackscore;
        continue;
      } else if (bking.getexist() == false) {
        std::cout << "--black king has been captured, white wins--"
                  << std::endl;
        ingame = false;
        ++whitescore;
        continue;
      }

      mycomputer.computer1(whichColour);
      myhelpers.switchturn(whichColour, whoseturn, blackPlayer, whitePlayer);
      firstmoved = !firstmoved;
      if (!firstmoved) round++;
    } else if (!(std::cin >> command)) {
      if (std::cin.eof()) {
        // print out the scores
        std::cout << "Final Score:" << std::endl;
        std::cout << "White: " << whitescore << std::endl;
        std::cout << "Black: " << blackscore << std::endl;
        break;
      }
      std::cin.clear();
      std::cin.ignore(10000, '\n');
      std::cout << "--Your command is not in the correct form, please input a "
                   "string--"
                << std::endl;

    } else if (command == "game") {
      ingame = true;
      std::cin >> whitePlayer;
      std::cin >> blackPlayer;
      if (whichColour == "white") {
        whoseturn = whitePlayer;
      } else {
        whoseturn = blackPlayer;
      }

      wkingmoved = false;
      bkingmoved = false;
      wrook2moved = false;
      wrook9moved = false;
      brook2moved = false;
      brook9moved = false;

      if (!setup) {
        myboard->initialBoard();
        wking.setxy(7, 6);
        wking.setexist(true);
        bking.setxy(0, 6);
        bking.setexist(true);
      } else {
      }
      myboard->printBoard();
      setup = false;
    }

    else if (command == "resign") {
      ingame = false;
      if (whichColour == "white") {
        std::cout << "--White resigns! Black wins!--" << std::endl;
        ++blackscore;
        continue;
      };
      if (whichColour == "black") {
        std::cout << "--Black resigns! White wins!--" << std::endl;
        ++whitescore;
        continue;
      };
    }

    else if (command == "move") {
      char firstx;
      int locy;
      char secondx;
      int desty;
      std::cin >> firstx;
      std::cin >> locy;
      std::cin >> secondx;
      std::cin >> desty;

      // transforming char to int
      int locx = firstx - 'a' + 2;
      int destx = secondx - 'a' + 2;

      // get the coordinates of location and destination of the board
      int movefromx = 8 - locy;
      int movefromy = locx;
      int movetox = 8 - desty;
      int movetoy = destx;

      // check if the location and destination of the pieces are out of bounds
      if (!(myhelpers.checkBounds(movefromx, movefromy) &&
            myhelpers.checkBounds(movetox, movetoy))) {
        std::cout << "--Out of bounds, please input again--" << std::endl;
        continue;
      }

      char loc = myboard->getPiece(movefromx, movefromy);
      char dest = myboard->getPiece(movetox, movetoy);

      // check whether loc is the correct colour
      if (ingame) {
        if (whichColour == "white") {
          if (!myhelpers.whitePiece(loc)) {
            std::cout << "--Not your piece, please move again--" << std::endl;
            continue;
          }
        } else if (whichColour == "black") {
          if (!myhelpers.blackPiece(loc)) {
            std::cout << "--Not your piece, please move again--" << std::endl;
            continue;
          }
        }
      }

      if (myhelpers.canGo(loc, dest)) {
        // check castling
        if (loc == 'k' && std::abs(movefromy - movetoy) == 2) {
          if (bkingmoved) {
            std::cout << "--Black king have moved, cannot castling--"
                      << std::endl;
            continue;
          }
          if ((movetoy > movefromy) && brook9moved) {
            std::cout << "--Black rook have moved, cannot castling--"
                      << std::endl;
            continue;
          } else if ((movetoy < movefromy) && brook2moved) {
            std::cout << "--Black rook have moved, cannot castling--"
                      << std::endl;
            continue;
          }
        } else if (loc == 'K' && std::abs(movefromy - movetoy) == 2) {
          if (wkingmoved) {
            std::cout << "--White king have moved, cannot castling--"
                      << std::endl;
            continue;
          }
          if ((movetoy > movefromy) && wrook9moved) {
            std::cout << "--White rook have moved, cannot castling--"
                      << std::endl;
            continue;
          } else if ((movetoy < movefromy) && wrook2moved) {
            std::cout << "--White rook have moved, cannot castling--"
                      << std::endl;
            continue;
          }
        }

        bool ItMoved = myhelpers.moved(myboard, loc, dest, movefromx, movefromy,
                                       movetox, movetoy);

        if (ItMoved) {
          if (loc == 'k') {
            bking.setxy(movetox, movetoy);
          } else if (loc == 'K') {
            wking.setxy(movetox, movetoy);
          } else
              // check arrive at the end of the board
              if (loc == 'p' && movetox == 7) {
            std::cout << "--Reached the other end, type r/n/b/q to replace p--"
                      << std::endl;
            std::cin >> loc;
            myboard->setPiece(loc, movetox, movetoy);
            // myboard->setEmpty(movefromx, movefromy);
            myboard->printBoard();
          } else if (loc == 'P' && movetox == 0) {
            std::cout << "--Reached the other end, type R/N/B/Q to replace P--"
                      << std::endl;
            std::cin >> loc;
            myboard->setPiece(loc, movetox, movetoy);
            // myboard->setEmpty(movefromx, movefromy);
            myboard->printBoard();
          }

          // check check
          // if (whichColour == "white") {
          if (myhelpers.checkcapture(myboard, bking.getx(), bking.gety(),
                                     'k')) {
            std::cout << "--Black is in check.--" << std::endl;
          }
          //} else {
          if (myhelpers.checkcapture(myboard, wking.getx(), wking.gety(),
                                     'K')) {
            std::cout << "--White is in check.--" << std::endl;
          }
          //}

          // check capture
          if (dest == 'k') {
            std::cout << "--Black king has been captured! White wins!--"
                      << std::endl;
            ingame = false;
            ++whitescore;
          } else if (dest == 'K') {
            std::cout << "--White king has been captured! Black wins!--"
                      << std::endl;
            ingame = false;
            ++blackscore;
          }

          if (loc == 'k' && bkingmoved == false) {
            bkingmoved = true;
          } else if (loc == 'K' && wkingmoved == false) {
            wkingmoved = true;
          } else if (loc == 'R' && locx == 7 && locy == 2 &&
                     wrook2moved == false) {
            wrook2moved = true;
          } else if (loc == 'R' && locx == 7 && locy == 9 &&
                     wrook9moved == false) {
            wrook9moved = true;
          } else if (loc == 'r' && locx == 0 && locy == 2 &&
                     brook2moved == false) {
            brook2moved = true;
          } else if (loc == 'r' && locx == 0 && locy == 9 &&
                     brook9moved == false) {
            brook9moved = true;
          }

          myhelpers.switchturn(whichColour, whoseturn, blackPlayer,
                               whitePlayer);
          firstmoved = !firstmoved;
          if (!firstmoved) round++;
        } else {
          std::cout << "--Invalid move, please input again--" << std::endl;
        }
      }

    } else if (command == "setup") {
      if (ingame) {
        std::cout << "--In game, cannot enter setup mode--" << std::endl;
        continue;
      }
      setup = true;
      myboard->emptyBoard();
      myboard->printBoard();
      std::string cmd;

      while (std::cin >> cmd) {
        if (cmd == "+") {
          char p;
          char firstx;
          int locy;
          std::cin >> p;
          std::cin >> firstx;
          std::cin >> locy;
          if (!myhelpers.validPiece(p)) {
            std::cout << "--Invalid piece, please input again--" << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
          }
          int locx = firstx - 'a' + 2;
          int movetox = 8 - locy;
          int movetoy = locx;
          myboard->setPiece(p, movetox, movetoy);
          myboard->printBoard();
        } else if (cmd == "-") {
          char firstx;
          int locy;
          if (!(std::cin >> firstx) || !(std::cin >> locy)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
          }
          int locx = firstx - 'a' + 2;
          int movetox = 8 - locy;
          int movetoy = locx;
          myboard->setEmpty(movetox, movetoy);
          myboard->printBoard();
        } else if (cmd == "=") {
          std::string color;
          std::cin >> color;
          if (color == "white") whichColour = "white";
          if (color == "black") whichColour = "black";
        } else if (cmd == "done") {
          if (myhelpers.checkExitSetup(myboard)) {
            // search for king
            wking.setxy(-1, -1);
            wking.setexist(false);
            bking.setxy(-1, -1);
            bking.setexist(false);
            for (int i = 0; i <= 7; ++i) {
              for (int j = 2; j <= 9; ++j) {
                if (wking.getexist() && bking.getexist()) break;
                if (myboard->getPiece(i, j) == 'k') {
                  bking.setxy(i, j);
                  bking.setexist(true);
                } else if (myboard->getPiece(i, j) == 'K') {
                  wking.setxy(i, j);
                  wking.setexist(true);
                }
              }
            }
            // check check
            bool isKinginCheck = false;
            if (myhelpers.checkcapture(myboard, bking.getx(), bking.gety(),
                                       'k')) {
              isKinginCheck = true;
              std::cout << "--Black is in check, cannot exit setup mode--"
                        << std::endl;
              continue;
            }
            if (myhelpers.checkcapture(myboard, wking.getx(), wking.gety(),
                                       'K')) {
              isKinginCheck = true;
              std::cout << "--White is in check, cannot exit setup mode--"
                        << std::endl;
            }
            if (!isKinginCheck) {
              std::cout << "--Exit setup mode--" << std::endl;
              break;
            } else {
              continue;
            }

          } else {
            continue;
          }
        } else {
          std::cout << "--Incorect command for set up, please input again--"
                    << std::endl;

          std::cin.clear();
          std::cin.ignore(10000, '\n');
          continue;
        }
      }
    }

    else if (command == "computer") {
      mycomputer.computer1("black");

    } else if (command == "skip") {
      myhelpers.switchturn(whichColour, whoseturn, blackPlayer, whitePlayer);
      firstmoved = !firstmoved;
      if (!firstmoved) round++;

    } else {  // none of the command above
      std::cout << "--Incorect command, please input again--" << std::endl;
      std::cin.clear();
      std::cin.ignore(10000, '\n');
      continue;
    }
  }

  delete myboard;
  delete mypieces;
}