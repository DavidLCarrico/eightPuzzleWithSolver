// Names of Contributors: David Carrico
#include <cstdlib>
#include <ctime>
#include <unordered_map>
#include "eightPuzzle.hpp"

const std::pair<size_t, size_t> indexOf[8] = {{0, 0}, {0, 1}, {0, 2}, {1, 0}, {1, 1}, {1, 2}, {2, 0}, {2, 1}};

eightPuzzle::eightPuzzle()
{
    unsigned char number = 1;

    for (size_t i =  0; i < 3; ++i)
    {
        for (size_t j = 0; j < 3; ++j)
        {
            board[i][j] = number++ % 9;
        }
    }

    rowOfZero = 2;
    columnOfZero = 2;
}

const eightPuzzle& eightPuzzle::operator=(const eightPuzzle &otherPuzzle)
{
    for (size_t i = 0; i < 3; ++i)
    {
        for (size_t j = 0; j < 3; ++j)
        {
            board[i][j] = otherPuzzle.board[i][j];
        }
    }

    rowOfZero = otherPuzzle.rowOfZero;
    columnOfZero = otherPuzzle.columnOfZero;

    return *this;
}

bool eightPuzzle::operator==(const eightPuzzle &otherPuzzle) const
{
    for (size_t i = 0; i < 3; ++i)
    {
        for (size_t j = 0; j < 3; ++j)
        {
            if (board[i][j] != otherPuzzle.board[i][j])
            {
                return false;
            }
        }
    }

    return true;
}

bool eightPuzzle::operator!=(const eightPuzzle &otherPuzzle) const
{
    for (size_t i = 0; i < 3; ++i)
    {
        for (size_t j = 0; j < 3; ++j)
        {
            if (board[i][j] != otherPuzzle.board[i][j])
            {
                return true;
            }
        }
    }

    return false;
}

size_t eightPuzzle::saxHash() const
{
    size_t h = 0;
    for (size_t i = 0; i < 3; ++i)
    {
        for (size_t j = 0; j < 3; ++j)
        {
            h ^= (h << 5) + (h >> 2) + board[i][j];
        }
    }

    return (h >> 14) ^ (h & 0x3ffff);
}


size_t eightPuzzle::manhattanDist() const
{
    size_t distance = 0;

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            unsigned char tile = board[i][j];
            if (tile)
            {
                std::pair<size_t, size_t> index = indexOf[tile - 1];
                distance += abs(i - index.first) + abs(j - index.second);
            }
        }
    }

    return distance;
}

void eightPuzzle::scramble()
{
    std::srand(std::time(nullptr));

    for (size_t i = 0; i < 3; ++i)
    {
        for (size_t j = 0; j < 3; ++j)
        {
            unsigned char value;
            do
            {
                value = std::rand() % 9;
            }
            while (!isNewValue(value, i, j));

            board[i][j] = value;
            if (value == 0)
            {
                rowOfZero = i;
                columnOfZero = j;
            }
        }
    }

    // If the puzzle is not solvable, this swaps two tiles to make it solvable.
    if (numberOfInversions() % 2)
    {
        size_t rowWithoutZero = (rowOfZero + 1) % 3;
        unsigned char temp = board[rowWithoutZero][0];
        board[rowWithoutZero][0] = board[rowWithoutZero][1];
        board[rowWithoutZero][1] = temp;
    }
}

bool eightPuzzle::move(char direction)
{
    bool validMove = false;

    switch (direction)
    {
        case 'u':
            if (rowOfZero < 2)
            {
                board[rowOfZero][columnOfZero] = board[rowOfZero + 1][columnOfZero];
                board[++rowOfZero][columnOfZero] = 0;

                validMove = true;
            }
            break;
        case 'd':
            if (rowOfZero > 0)
            {
                board[rowOfZero][columnOfZero] = board[rowOfZero - 1][columnOfZero];
                board[--rowOfZero][columnOfZero] = 0;

                validMove = true;
            }
            break;
        case 'l':
            if (columnOfZero < 2)
            {
                board[rowOfZero][columnOfZero] = board[rowOfZero][columnOfZero + 1];
                board[rowOfZero][++columnOfZero] = 0;

                validMove = true;
            }
            break;
        case 'r':
            if (columnOfZero > 0)
            {
                board[rowOfZero][columnOfZero] = board[rowOfZero][columnOfZero - 1];
                board[rowOfZero][--columnOfZero] = 0;

                validMove = true;
            }
            break;
    }

    return validMove;
}

void eightPuzzle::print() const
{
    std::cout << std::endl;
    for (size_t i = 0; i < 3; ++i)
    {
        for (size_t j = 0; j < 3; ++j)
        {
            if (board[i][j])
            {
                std::cout << static_cast<unsigned int>(board[i][j]);
            }
            else
            {
                std::cout << ' ';
            }
        }
        std::cout << std::endl;
    }
}

bool eightPuzzle::isSolved() const
{
    unsigned char goal[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};

    for (size_t i = 0; i < 3; ++i)
    {
        for (size_t j = 0; j < 3; ++j)
        {
            if (board[i][j] != goal[i][j])
            {
                return false;
            }
        }
    }

    return true;
}

bool eightPuzzle::isNewValue(unsigned char value, size_t row, size_t column) const
{
    for (size_t i = 0; i < 3; ++i)
    {
        for (size_t j = 0; j < 3; ++j)
        {
            if ((i < row || j < column) && value == board[i][j])
            {
                return false;
            }
        }
    }

    return true;
}

size_t eightPuzzle::numberOfInversions() const
{
    size_t index = 0;
    unsigned char list[8];

    for (size_t i = 0; i < 3; ++i)
    {
        for (size_t j = 0; j < 3; ++j)
        {
            if (board[i][j])
            {
                list[index++] = board[i][j];
            }
        }
    }

    size_t totalNumberOfInversions = 0;
    for (index = 0; index < 8; ++index)
    {
        for (size_t following = index + 1; following < 8; ++following)
        {
            if (list[index] > list[following])
            {
                ++totalNumberOfInversions;
            }
        }
    }

    return totalNumberOfInversions;
}
