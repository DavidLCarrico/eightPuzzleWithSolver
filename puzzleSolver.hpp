// Names of Contributors: David Carrico
#ifndef SOLVER_H
#define SOLVER_H
#include <queue>
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
        void expandNode(treeNode tNode);
        void setRoot(const eightPuzzle &state);
        bool addNode(char move, treeNode parentNode);
        void buildSolution(treeNode goalNode);
        void deleteTree();
        std::stack<char> solution;
        std::unordered_set<treeNode, treeNode::hash> nodesInTree;
        std::priority_queue<treeNode> fringe;
        bool foundSolution;
};

#endif
