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
        struct saxHash // This should be the shift-add-XOR hash <http://eternallyconfuzzled.com/tuts/algorithms/jsw_tut_hashing.aspx> with xor folding
        {
            inline unsigned int operator()(const eightPuzzle &state) const
            {
                unsigned int h = 0;
                for (int i = 0; i < 3; ++i)
                {
                    for (int j = 0; j < 3; ++j)
                    {
                        h ^= (h << 5) + (h >> 2) + state.board[i][j];
                    }
                }

                return (h >> 14) ^ (h & 0x3ffff);
            }
        };
        int hammingDist() const;
        void scramble();
        bool move(char direction);
        void print() const;
        bool isSolved() const;
    private:
        bool isNewValue(short int value, int row, int column) const;
        int numberOfInversions() const;
        int rowOfZero;
        int columnOfZero;
        short int board[3][3];
};

#endif
