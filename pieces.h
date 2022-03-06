#ifndef _PIECES_H_
#define _PIECES_H_

class Pieces {
private:
    /* data */
public:
    virtual int canMove(int locx, int locy, int destx, int desty) = 0;
    virtual ~Pieces();
};






#endif