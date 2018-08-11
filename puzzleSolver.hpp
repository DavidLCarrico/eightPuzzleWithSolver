// Names of Contributors: David Carrico
#ifndef SOLVER_H
#define SOLVER_H
#include <queue>
#include <vector>
#include <stack>
#include <unordered_set>
#include "eightPuzzle.hpp"
#include "treeNode.hpp"

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
        std::unordered_set<eightPuzzle, eightPuzzle::fnvHash> statesInTree;
        std::priority_queue<treeNode*, std::vector<treeNode*>, cmpNodes> fringe; 
        bool foundSolution;
};

#endif
