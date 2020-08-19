CC = g++
CPPFLAGS = -Wall -Wextra -Werror -g
objects = puzzleSolverImp.o treeNodeImp.o eightPuzzleImp.o main.o

all: puzzleGame

puzzleGame: $(objects)
	$(CC) $(CPPFLAGS) -o puzzleGame $(objects)

$(objects): eightPuzzle.hpp treeNode.hpp puzzleSolver.hpp

.PHONY: cleanobjects
cleanobjects:
	-rm $(objects)

.PHONY: clean
clean:
	-rm puzzleGame $(objects)
