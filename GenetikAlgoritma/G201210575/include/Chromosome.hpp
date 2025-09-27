#ifndef CHROMOSOME_HPP
#define CHROMOSOME_HPP

#include <iostream>
#include "Node.hpp"

class Chromosome
{
public:
    Node *head;
    Node *tail;

    Chromosome();
    ~Chromosome();
    void addGene(char gene);
    int getSize() const;
    friend std::ostream &operator<<(std::ostream &screen, const Chromosome &right);
};

#endif
