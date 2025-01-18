#ifndef NODE_HPP
#define NODE_HPP

#include "BinaryTree.hpp"

class Node
{
public:
    BinaryTree *tree;
    Node *next;

    Node(BinaryTree *tree);
    ~Node();
};

#endif
