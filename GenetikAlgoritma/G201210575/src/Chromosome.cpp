/**
 * @file Chromosome.cpp
 * @description Bagli Liste ile Gen Kromozom ve DNA Projesi
 * @course Veri Yapilari 2-B
 * @assignment 1.Ödev
 * @date 26.11.2024
 * @author Nargiza Zhyrgalbek Kyzy nargiza.kyzy@ogr.sakarya.edu.tr
 */

#include "Chromosome.hpp"

Chromosome::Chromosome() : head(nullptr) {}

Chromosome::~Chromosome()
{
    Node *current = head;
    while (current)
    {
        Node *temp = current;
        current = current->next;
        delete temp;
    }
}

void Chromosome::addGene(char gene)
{
    Node *newNode = new Node(gene);
    if (!head)
    {
        head = newNode;
        tail = newNode;
    }
    else
    {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

std::ostream &operator<<(std::ostream &screen, const Chromosome &right)
{
    for (Node *temp = right.head; temp != NULL; temp = temp->next)
        screen << temp->gene << ' ';
    return screen;
}

int Chromosome::getSize() const
{
    int size = 0;
    Node *temp = head;
    while (temp)
    {
        size++;
        temp = temp->next;
    }
    return size;
}
