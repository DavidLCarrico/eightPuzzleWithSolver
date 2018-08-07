// Names of Contributors: David Carrico
#ifndef TREE_NODE_H
#define TREE_NODE_H
#include "eightPuzzle.hpp"

struct treeNode
{
    eightPuzzle state;
    int length;
    char move;
    treeNode *parent;
};

struct cmpNodes
{
    bool operator()(const treeNode *first, const treeNode *second) const
    {
        return first->length + first->state.hammingDist() > second->length + second->state.hammingDist();
    }
};

#endif
