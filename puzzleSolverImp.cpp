// Names of Contributors: David Carrico
#include "puzzleSolver.hpp"

puzzleSolver::puzzleSolver()
{
    foundSolution = false;
}

void puzzleSolver::solve(const eightPuzzle &state)
{
    treeNode tNode;

    foundSolution = state.isSolved();

    setRoot(state);
    while (!foundSolution)
    {
        tNode = fringe.top();
        fringe.pop();
        expandNode(tNode);
    }

    deleteTree();
}

char puzzleSolver::getMove()
{
    char move = solution.top();

    solution.pop();

    return move;
}

puzzleSolver::~puzzleSolver()
{
    deleteTree();
}

void puzzleSolver::expandNode(treeNode path)
{
    bool addedNode = false;
    
    for (int i = 0; i < 4; ++i)
    {
        switch (i)
        {
            case 0:
                addedNode = addNode('u', path);
                break;
            case 1:
                addedNode = addNode('r', path);
                break;
            case 2:
                addedNode = addNode('d', path);
                break;
            case 3:
                addedNode = addNode('l', path);
                break;
        }

        treeNode highestPriorityNode = fringe.top();
        if (addedNode && highestPriorityNode.getState().isSolved())
        {
            foundSolution = true;
            buildSolution(highestPriorityNode);
            break;
        }
    }
}

void puzzleSolver::setRoot(const eightPuzzle &state)
{
    treeNode newNode;

    newNode.setState(state);
    newNode.setLength(0);
    newNode.setMove('\0');
    newNode.setParent(nullptr);

    fringe.push(newNode);
    nodesInTree.insert(newNode);
}

bool puzzleSolver::addNode(char m, treeNode parentNode)
{
    eightPuzzle newState;

    newState = parentNode.getState();

    if (newState.move(m))
    {
        if (!parentNode.getParent() || newState != parentNode.getParent()->getState())
        {
            treeNode newNode;
            std::unordered_set<treeNode>::iterator parent = nodesInTree.find(parentNode);

            newNode.setState(newState);
            newNode.setLength(parentNode.getLength() + 1);
            newNode.setMove(m);
            newNode.setParent(&*parent);

            fringe.push(newNode);
            nodesInTree.insert(newNode);

            return true;
        }
    }

    return false;
}

void puzzleSolver::buildSolution(treeNode goalNode)
{
    const treeNode *temp = &goalNode;
    while (temp)
    {
        char move = temp->getMove();
        if (move)
        {
            solution.push(move);
        }
        temp = temp->getParent();
    }
}

void puzzleSolver::deleteTree()
{
    while (!fringe.empty())
    {
        fringe.pop();
    }

    nodesInTree.clear();
}
