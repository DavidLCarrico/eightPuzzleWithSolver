all: puzzleGame.bin

puzzleGame.bin: main.o eightPuzzleImp.o puzzleSolverImp.o
	g++ -Wall -g -o puzzleGame.bin main.o eightPuzzleImp.o puzzleSolverImp.o

main.o: main.cpp
	g++ -Wall -g -c main.cpp

eightPuzzleImp.o: eightPuzzleImp.cpp
	g++ -Wall -g -c eightPuzzleImp.cpp

puzzleSolverImp.o: puzzleSolverImp.cpp
	g++ -Wall -g -c puzzleSolverImp.cpp

clean:
	rm *.o
