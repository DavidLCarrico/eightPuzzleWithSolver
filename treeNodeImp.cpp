// Names of contributors: David Carrico
#include "treeNode.hpp"

bool treeNode::operator<(const treeNode &otherNode) const
{
        return length + state.manhattanDist() >
            otherNode.length + otherNode.state.manhattanDist();
};

bool treeNode::operator==(const treeNode &otherNode) const
{
    return state == otherNode.state && length == otherNode.length
        && move == otherNode.move && parent == otherNode.parent;
}

void treeNode::setState(const eightPuzzle &givenState)
{
    state = givenState;
}

const eightPuzzle & treeNode::getState() const
{
    return state;
}

void treeNode::setLength(size_t givenLength)
{
    length = givenLength;
}

size_t treeNode::getLength() const
{
    return length;
}

void treeNode::setMove(char givenMove)
{
    move = givenMove;
}

char treeNode::getMove() const
{
    return move;
}

void treeNode::setParent(const treeNode *givenParent)
{
    parent = givenParent;
}

const treeNode * treeNode::getParent() const
{
    return parent;
}
