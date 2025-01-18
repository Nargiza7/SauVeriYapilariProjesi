#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include "Node.hpp"

class LinkedList
{
private:
    Node *head;
    Node *tail;
    Node *current;

public:
    LinkedList();
    ~LinkedList();
    void add(BinaryTree *tree);
    int NodeCount() const;
    Node *nodePosition(int index) const;
    void display(int start, int count) const;
    void cizgiCizdir(int adet) const;
    void boslukBirak(int sira) const;
    void Yazdir(int bas, int son);
    BinaryTree *getNode(int index) const;
    void displayWithIndicator(int currentIndex, int pageSize) const;
    Node *getNodeAt(int index) const;
    void remove(int index);
};

#endif
