// Names of Contributors: David Carrico
#ifndef PUZZLE_H
#define PUZZLE_H
#include <iostream>

class eightPuzzle
{
    public:
        eightPuzzle();
        const eightPuzzle& operator=(const eightPuzzle &otherPuzzle);
        bool operator==(const eightPuzzle &otherPuzzle) const;
        size_t manhattanDist() const;
        void scramble();
        bool move(char direction);
        void print() const;
        bool isSolved() const;
    private:
        bool isNewValue(short int value, int row, int column) const;
        int numberOfInversions() const;
        short int board[3][3];
        int rowOfZero;
        int columnOfZero;
};

#endif
