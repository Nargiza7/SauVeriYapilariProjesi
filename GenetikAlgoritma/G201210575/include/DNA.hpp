#ifndef DNA_HPP
#define DNA_HPP

#include "Chromosome.hpp"

struct ChromosomeNode
{
    Chromosome *chromosome;
    ChromosomeNode *next;

    ChromosomeNode(Chromosome *chrom) : chromosome(chrom), next(nullptr) {}
};

class DNA
{
private:
    ChromosomeNode *head;
    ChromosomeNode *tail;
    int chromosomeCount;

public:
    DNA();
    ~DNA();

    void addChromosome(Chromosome *chromosome);
    friend std::ostream &operator<<(std::ostream &screen, const DNA &right);
    void crossOver(int index1, int index2);
    void mutate(int chromosomeIndex, int geneIndex);
    void performAutomaticOperations(const std::string &operationsFile);
    void writeToScreen() const;
    Chromosome *getChromosome(int index) const;
};

#endif
