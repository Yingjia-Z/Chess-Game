#ifndef _NOPIECES_H_
#define _NOPIECES_H_
#include "pieces.h"

class NoPieces : public Pieces {
 private:
  /* data */
 public:
  int canMove(int locx, int locy, int destx, int desty) override;
};

#endif