// Names of Contributors: David Carrico
#include "puzzleSolver.hpp"

puzzleSolver::puzzleSolver()
{
    foundSolution = false;
}

void puzzleSolver::solve(const eightPuzzle &state)
{
    treeNode *tNode;

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

void puzzleSolver::expandNode(treeNode *path)
{
    treeNode *addedNode;
    
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

        if (addedNode && addedNode->state.isSolved())
        {
            foundSolution = true;
            buildSolution(addedNode);
            break;
        }
    }
}

void puzzleSolver::setRoot(const eightPuzzle & state)
{
    treeNode *newNode = new treeNode;

    newNode->state = state;
    newNode->length = 0;
    newNode->move = '\0';
    newNode->parent = nullptr;

    fringe.push(newNode);
    nodesInTree.push_back(newNode);
}

treeNode* puzzleSolver::addNode(char m, treeNode *parentNode)
{
    treeNode *newNode = new treeNode;

    newNode->state = parentNode->state;
    newNode->move = m;
    newNode->state.move(m);

    newNode->parent = parentNode;
    newNode->length = parentNode->length + 1;

    if (parentNode->parent && newNode->state == parentNode->parent->state)
    {
        delete newNode;
        newNode = nullptr;
    }
    else
    {
        fringe.push(newNode);
        nodesInTree.push_back(newNode);
    }

    return newNode;
}

void puzzleSolver::buildSolution(treeNode *goalNode)
{
    treeNode *temp = goalNode;
    while (temp)
    {
        if (temp->move)
        {
            solution.push(temp->move);
        }
        temp = temp->parent;
    }
}

void puzzleSolver::deleteTree()
{
    while (!fringe.empty())
    {
        fringe.pop();
    }

    for (treeNode *&tNode: nodesInTree)
    {
        if (tNode)
        {
            delete tNode;
        }
    }

    nodesInTree.clear();
}
