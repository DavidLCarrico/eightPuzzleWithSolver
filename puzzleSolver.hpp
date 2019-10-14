// Names of Contributors: David Carrico
#ifndef SOLVER_H
#define SOLVER_H
#include <queue>
#include <vector>
#include <stack>
#include "eightPuzzle.hpp"

struct treeNode
{
    eightPuzzle state;
    size_t length;
    char move;
    treeNode *parent;
};

struct comparePath
{
    inline bool operator()(const treeNode *first, const treeNode *second) const
    {
        return first->length + first->state.manhattanDist() > second->length + second->state.manhattanDist();
    }
};

class puzzleSolver
{
    public:
        puzzleSolver();
        void solve(const eightPuzzle &state);
        char getMove();
        ~puzzleSolver();
    private:
        void expandNode(treeNode *tNode);
        void setRoot(const eightPuzzle &state);
        treeNode* addNode(char move, treeNode *parentNode);
        void buildSolution(treeNode *goalNode);
        void deleteTree();
        std::stack<char> solution;
        std::vector<treeNode*> nodesInTree;
        std::priority_queue<treeNode*, std::vector<treeNode*>, comparePath> fringe;
        bool foundSolution;
};

#endif
