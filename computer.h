#include "board.h"

class Computer {
 private:
  Board* myboard;

 public:
  Computer(Board* b);
  ~Computer();
  void computer1(std::string whichColour);
  void computer2(std::string whichColour);

  // auotmaticaly find a dest that the piece can move to
  void autoMove1(Board* myboard, char loc, int movefromx, int movefromy,
                 int movetox, int movetoy, bool print = true);
};
