// Names of contributors: David Carrico
#ifndef TREE_NODE_H
#define TREE_NODE_H
#include "eightPuzzle.hpp"

class treeNode
{
    public:
        bool operator<(const treeNode &otherNode) const;
        bool operator==(const treeNode &otherNode) const;
        struct hash
        {
            inline size_t operator()(const treeNode &givenNode) const
            {
                return givenNode.state.saxHash();
            }
        };
        void setState(const eightPuzzle &givenState);
        const eightPuzzle & getState() const;
        void setLength(size_t givenLength);
        size_t getLength() const;
        void setMove(char givenMove);
        char getMove() const;
        void setParent(const treeNode *givenParent);
        const treeNode * getParent() const;
    private:
        eightPuzzle state;
        size_t length;
        char move;
        const treeNode *parent;
};

#endif
