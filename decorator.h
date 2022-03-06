#ifndef _DECORATOR_H_
#define _DECORATOR_H_
#include "board.h"
#include "pieces.h"

class Decorator : public Pieces {
 protected:
  Board* b;

 public:
  Decorator(Board* b);
  virtual ~Decorator();
};

#endif