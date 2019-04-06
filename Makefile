CC = g++
CPPFLAGS = -Wall -Wextra -Werror -O4
objects = puzzleSolverImp.o eightPuzzleImp.o main.o

all: puzzleGame

puzzleGame: main.o eightPuzzleImp.o puzzleSolverImp.o
	$(CC) $(CPPFLAGS) -o puzzleGame main.o eightPuzzleImp.o puzzleSolverImp.o

$(objects): eightPuzzle.hpp puzzleSolver.hpp

.PHONY: cleanobjects
cleanobjects:
	-rm $(objects)

.PHONY: clean
clean:
	-rm puzzleGame $(objects)
