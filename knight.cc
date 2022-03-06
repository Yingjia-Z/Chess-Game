#include "knight.h"

#include <cmath>

Knight::Knight(Board* b) : Decorator{b} {}

int Knight::canMove(int locx, int locy, int destx, int desty) {
  // can jump, no need to check jump
  if ((std::abs(locx - destx) == 2 && std::abs(locy - desty) == 1) ||
      (std::abs(locx - destx) == 1 && std::abs(locy - desty) == 2)) {
    return 1;
  } else {
    return 0;
  }
}