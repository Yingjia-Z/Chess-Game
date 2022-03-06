# Chess-Game

This program implement the chess game in C++. It utilizes decorator design patterns, separate compilation, object- oriented programming. Inputs are read in by console and the outputs are printed to screen.

## The program consists of several interfaces and each of them contains one or more class:

### main.cc: 
is the test harness of the program, it reads in the inputs and calls the related functions from other classes. It provides a platform for players to interact with the program.

### chesshelpers.h:
is where all the helper functions are stored by organizing them into a class. In main.cc, we created a class of ChessHelpers to call the related functions when necessary. Methods are in ChessHelpers also responsible for some error message outputting. // and coordinates class

### board.h:
contains the class Board, it is responsible for setting pieces, retrieving pieces, initializing the checkerboard and printing the checkerboard.

### decorator.h, pieces.h, noPieces.h:
are the components of decorator design patterns, they contain a method canMove to determine if it is a valid move for a kind of pieces.

### bishop.h, king.h, knight.h, pawn.h, queen.h, rook.h:
are the concrete decorators, they are specified to contain the unique moving rules, capturing rules and special moves of the pieces.

### computer.h:
contains the class Computer. Computer is responsible for running computer1, which randomly moves pieces.

#### See demo.pdf and design.pdf for more information.
