// Names of Contributors: David Carrico
// For more information on the eight puzzle visit https://www.cs.princeton.edu/courses/archive/spr10/cos226/assignments/8puzzle.html
#include <cctype>
#include <limits>
#include "eightPuzzle.hpp"
#include "puzzleSolver.hpp"

char getChar();

int main()
{
    eightPuzzle grid;
    puzzleSolver ai;
    char choice = '\0', direction = '\0';
    int numberOfMoves;

    std::cout << "Welcome to the eight puzzle game!" << std::endl;
    do
    {
        grid.scramble();
        numberOfMoves = 0;
        do
        {
            grid.print();
            std::cout << "\nWould you like to make a (m)ove, (r)escramble the puzzle, let me (s)olve the puzzle, or (q)uit? ";
            choice = getChar();

            switch (choice)
            {
                case 'm': 
                    std::cout << "\nWould you like to move (u)p, (d)own, (r)ight, or (l)eft? ";
                    direction = getChar();
                    if (grid.move(direction))
                    {
                        ++numberOfMoves;
                    }
                    else
                    {
                        std::cout << "\nInvalid move!" << std::endl;
                    }
                    break;
                case 's':
                    ai.solve(grid);
                    while (!grid.isSolved())
                    {
                        direction = ai.getMove();
                        grid.move(direction);
                        grid.print();
                    }
                    break;
                case 'r':
                    grid.scramble();
                    numberOfMoves = 0;
                    break;
                case 'q':
                    break;
                default:
                    std::cout << "\nInvalid choice!" << std::endl;
            }
        }
        while (!grid.isSolved() && choice != 'q');

        if (grid.isSolved())
        {
            if (choice != 's')
            {
                grid.print();
                std::cout << "\nCongratulations, you solved this puzzle in " << numberOfMoves << " moves!!!";
            }
            else
            {
                std::cout << "\nHaha, I win!";
            }

            std::cout << "\n\nWould you like to play again (y/n)? ";
            choice = getChar();
        }
    }
    while (choice == 'y');

    return 0;
}

char getChar()
{
    char character = '\0';

    std::cin.get(character);
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return std::tolower(character);
}
