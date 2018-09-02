// Names of Contributors: David Carrico
#ifndef SOLVER_H
#define SOLVER_H
#include <queue>
#include <vector>
#include <stack>
#include <unordered_set>
#include "eightPuzzle.hpp"

struct treeNode
{
    eightPuzzle state;
    int length;
    char move;
    treeNode *parent;
};

struct comparePath
{
    inline bool operator()(const treeNode *first, const treeNode *second) const
    {
        return first->length + first->state.hammingDist() > second->length + second->state.hammingDist();
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
        std::unordered_set<eightPuzzle, eightPuzzle::saxHash> statesInTree;
        std::priority_queue<treeNode*, std::vector<treeNode*>, comparePath> fringe; 
        bool foundSolution;
};

#endif
