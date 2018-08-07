// Names of Contributors: David Carrico
// For more information on the eight puzzle visit https://www.cs.princeton.edu/courses/archive/spr10/cos226/assignments/8puzzle.html
#include <cctype>
#include <limits>
#include "eightPuzzle.hpp"
#include "puzzleSolver.hpp"

char getMove();

int main()
{
    eightPuzzle grid;
    puzzleSolver ai;
    char choice = '\0', direction = '\0';

    std::cout << "Welcome to the eight puzzle game!" << std::endl;
    do
    {
        grid.scramble();
        do
        {
            grid.print();
            std::cout << "\nWould you like to make a (m)ove, (r)escramble the puzzle, let me (s)olve the puzzle, or (q)uit? ";
            std::cin.get(choice);
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            choice = std::tolower(choice);
            switch (choice)
            {
                case 'm': 
                    direction = getMove();
                    if (grid.move(direction))
                    {
                        std::cout << "\nMove was successful." << std::endl;
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
                std::cout << "\nCongratulations, you win!!!";
            }
            else
            {
                std::cout << "\nHaha, I win!";
            }
            std::cout << "\n\nWould you like to play again (y/n)? ";
            std::cin.get(choice);
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            choice = std::tolower(choice);
        }
    }
    while (choice == 'y');

    return 0;
}

char getMove()
{
    char direction = '\0';

    std::cout << "\nWould you like to move (u)p, (d)own, (r)ight, or (l)eft? ";
    std::cin.get(direction);
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return std::tolower(direction);
}
