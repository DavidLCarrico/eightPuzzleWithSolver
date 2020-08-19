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
        bool operator!=(const eightPuzzle &otherPuzzle) const;
        // This should be the shift-add-XOR hash
        // <http://eternallyconfuzzled.com/tuts/algorithms/jsw_tut_hashing.aspx> with xor folding
        size_t saxHash() const;
        size_t manhattanDist() const;
        void scramble();
        bool move(char direction);
        void print() const;
        bool isSolved() const;
    private:
        bool isNewValue(unsigned char value, size_t row, size_t column) const;
        size_t numberOfInversions() const;
        unsigned char board[3][3];
        size_t rowOfZero;
        size_t columnOfZero;
};

#endif
