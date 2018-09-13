// Names of Contributors: David Carrico
#include <cstdlib>
#include <ctime>
#include <unordered_map>
#include "eightPuzzle.hpp"

const std::unordered_map<int, std::pair<int, int>> indexOf = {{1, {0, 0}}, {2, {0, 1}}, {3, {0, 2}}, {4, {1, 0}}, {5, {1, 1}}, {6, {1, 2}}, {7, {2, 0}}, {8, {2, 1}}};

eightPuzzle::eightPuzzle()
{
    short int number = 1;

    for (int i =  0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            board[i][j] = number++ % 9;
        }
    }

    rowOfZero = 2;
    columnOfZero = 2;
}

const eightPuzzle& eightPuzzle::operator=(const eightPuzzle &otherPuzzle)
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
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
    bool isEqual = true;

    for (int i = 0; isEqual && i < 3; ++i)
    {
        for (int j = 0; isEqual && j < 3; ++j)
        {
            isEqual = isEqual && board[i][j] == otherPuzzle.board[i][j];
        }
    }

    return isEqual;
}

int eightPuzzle::manhattanDist() const
{
    int dist = 0;
    std::unordered_map<int, std::pair<int, int>>::const_iterator it;

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            it = indexOf.find(board[i][j]);
            if (it != indexOf.end())
            {
                dist += abs(i - it->second.first) + abs(j - it->second.second);
            }
        }
    }

    return dist;
}

void eightPuzzle::scramble()
{
    std::srand(std::time(nullptr));

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            short int value;
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

    if (numberOfInversions() % 2)
    {
        int rowWithoutZero = (rowOfZero + 1) % 3;
        short int temp = board[rowWithoutZero][0];
        board[rowWithoutZero][0] = board[rowWithoutZero][1];
        board[rowWithoutZero][1] = temp;
    }
}

bool eightPuzzle::move(char direction)
{
    bool moveSuccessful = false;

    switch (direction)
    {
        case 'u':
            if (rowOfZero + 1 < 3)
            {
                board[rowOfZero][columnOfZero] = board[rowOfZero + 1][columnOfZero];
                board[++rowOfZero][columnOfZero] = 0;

                moveSuccessful = true;
            }
            break;
        case 'd':
            if (rowOfZero - 1 >= 0)
            {
                board[rowOfZero][columnOfZero] = board[rowOfZero - 1][columnOfZero];
                board[--rowOfZero][columnOfZero] = 0;

                moveSuccessful = true;
            }
            break;
        case 'l':
            if (columnOfZero + 1 < 3)
            {
                board[rowOfZero][columnOfZero] = board[rowOfZero][columnOfZero + 1];
                board[rowOfZero][++columnOfZero] = 0;

                moveSuccessful = true;
            }
            break;
        case 'r':
            if (columnOfZero - 1 >= 0)
            {
                board[rowOfZero][columnOfZero] = board[rowOfZero][columnOfZero - 1];
                board[rowOfZero][--columnOfZero] = 0;

                moveSuccessful = true;
            }
            break;
    }

    return moveSuccessful;
}

void eightPuzzle::print() const
{
    std::cout << std::endl;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (board[i][j])
            {
                std::cout << board[i][j];
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
    bool solved = true;
    short int goal[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};

    for (int i = 0; solved && i < 3; ++i)
    {
        for (int j = 0; solved && j < 3; ++j)
        {
            solved = solved && board[i][j] == goal[i][j];
        }
    }

    return solved;
}

bool eightPuzzle::isNewValue(short int value, int row, int column) const
{
    bool isNew = true;

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if ((i < row || j < column) && value == board[i][j])
            {
                isNew = false;
            }
        }
    }

    return isNew;
}

int eightPuzzle::numberOfInversions() const
{
    int index = 0, totalNumberOfInversions = 0;
    short int list[8];

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (board[i][j])
            {
                list[index++] = board[i][j];
            }
        }
    }

    for (index = 0; index < 8; ++index)
    {
        for (int following = index + 1; following < 8; ++following)
        {
            if (list[index] > list[following])
            {
                ++totalNumberOfInversions;
            }
        }
    }

    return totalNumberOfInversions;
}
