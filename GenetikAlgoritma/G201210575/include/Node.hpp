#ifndef NODE_HPP
#define NODE_HPP

class Node
{
public:
    char gene;
    Node *next;
    Node *prev;
    Node();
    Node(char g);
};

#endif
