CXX=g++
CXXFLAGS=-std=c++14 -Wall -MMD -g
OBJECTS=main.o bishop.o board.o chesshelpers.o computer.o decorator.o king.o knight.o noPieces.o pawn.o pieces.o queen.o rook.o  
DEPENDS=${OBJECTS:.o=.d}
EXEC=chess

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}
