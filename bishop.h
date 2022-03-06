#ifndef _BISHOP_H_
#define _BISHOP_H_
#include "decorator.h"
#include <cmath>
class Pieces;

class Bishop: public Decorator {
private:
    /* data */
public:
    Bishop(Board * b);
    int canMove (int locx, int locy, int destx, int desty) override;
};


#endif