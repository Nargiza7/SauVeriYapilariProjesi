/**
 * @file DNA.cpp
 * @description Bagli Liste ile Gen Kromozom ve DNA Projesi
 * @course Veri Yapilari 2-B
 * @assignment 1.Ödev
 * @date 26.11.2024
 * @author Nargiza Zhyrgalbek Kyzy nargiza.kyzy@ogr.sakarya.edu.tr
 */

#include <iostream>
#include "DNA.hpp"
#include <sstream>
#include <fstream>

DNA::DNA() : head(nullptr), tail(nullptr), chromosomeCount(0) {}

DNA::~DNA()
{
    ChromosomeNode *current = head;
    while (current)
    {
        ChromosomeNode *toDelete = current;
        delete current->chromosome;
        current = current->next;
        delete toDelete;
    }
}

void DNA::addChromosome(Chromosome *chromosome)
{
    ChromosomeNode *newNode = new ChromosomeNode(chromosome);
    if (!head)
    {
        head = tail = newNode;
    }
    else
    {
        tail->next = newNode;
        tail = newNode;
    }
    chromosomeCount++;
}

Chromosome *DNA::getChromosome(int index) const
{
    if (index < 0 || index >= chromosomeCount)
    {
        std::cerr << "Geçersiz kromozom numarası!" << std::endl;
        return nullptr;
    }
    ChromosomeNode *current = head;
    for (int i = 0; i < index; ++i)
    {
        current = current->next;
    }
    return current->chromosome;
}

std::ostream &operator<<(std::ostream &screen, const DNA &right)
{
    for (ChromosomeNode *temp = right.head; temp != NULL; temp = temp->next)
        screen << *temp->chromosome << std::endl;
    return screen;
}

void DNA::crossOver(int index1, int index2)
{
    Chromosome *chrom1 = getChromosome(index1);
    Chromosome *chrom2 = getChromosome(index2);

    if (chrom1 == nullptr || chrom2 == nullptr)
    {
        std::cerr << "Gecersiz kromozom numaralari!" << std::endl;
        return;
    }

    int size1 = chrom1->getSize();
    int size2 = chrom2->getSize();

    int totalSize = size1 + size2;
    bool isTotalSizeEven = (totalSize % 2 == 0);

    int midpoint1 = size1 / 2;
    int midpoint2 = size2 / 2;

    Chromosome *newChromosome1 = new Chromosome();
    Chromosome *newChromosome2 = new Chromosome();

    Node *current = chrom1->head;
    for (int i = 0; i < midpoint1; ++i)
    {
        newChromosome1->addGene(current->gene);
        current = current->next;
    }

    if (size1 % 2 != 0 && current)
    {
        current = current->next;
    }

    current = chrom2->head;
    for (int i = 0; i < midpoint2; ++i)
    {
        current = current->next;
    }

    if (size2 % 2 != 0 && current)
    {
        current = current->next;
    }
    while (current)
    {
        newChromosome1->addGene(current->gene);
        current = current->next;
    }

    current = chrom1->head;
    for (int i = 0; i < midpoint1; ++i)
    {
        current = current->next;
    }

    if (size1 % 2 != 0 && current)
    {
        current = current->next;
    }
    while (current)
    {
        newChromosome2->addGene(current->gene);
        current = current->next;
    }

    current = chrom2->head;
    for (int i = 0; i < midpoint2; ++i)
    {
        newChromosome2->addGene(current->gene);
        current = current->next;
    }

    addChromosome(newChromosome1);
    addChromosome(newChromosome2);
}

void DNA::mutate(int chromosomeIndex, int geneIndex)
{
    Chromosome *chrom = getChromosome(chromosomeIndex);

    if (chrom == nullptr)
    {
        std::cerr << "Gecersiz kromozom numarasi!" << std::endl;
        return;
    }

    if (geneIndex < 0 || geneIndex >= chrom->getSize())
    {
        std::cerr << "Gecersiz gen numarasi!" << std::endl;
        return;
    }

    Node *current = chrom->head;

    for (int i = 0; i < geneIndex; ++i)
    {
        if (current == nullptr)
        {
            std::cerr << "Gen bulunamadi!" << std::endl;
            return;
        }
        current = current->next;
    }

    if (current != nullptr)
    {
        current->gene = 'X';
    }
    else
    {
        std::cerr << "Gen bulunamadi!" << std::endl;
    }
}

void DNA::performAutomaticOperations(const std::string &operationsFile)
{
    std::ifstream file(operationsFile);
    std::string line;

    if (!file.is_open())
    {
        std::cerr << "Dosya Acilamadi!" << std::endl;
        return;
    }

    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        char operation;
        int index1, index2;

        iss >> operation;

        if (operation == 'C')
        {
            iss >> index1 >> index2;
            crossOver(index1, index2);
        }
        else if (operation == 'M')
        {
            iss >> index1 >> index2;
            mutate(index1, index2);
        }
        else
        {
            std::cerr << "Dosyada gecersiz islem!" << std::endl;
        }
    }

    file.close();
    std::cout << "İslemler tamamlandi!" << std::endl;
}

void DNA::writeToScreen() const
{
    ChromosomeNode *currentNode = head;
    while (currentNode != nullptr)
    {
        Chromosome *chrom = currentNode->chromosome;

        char smallestGene = chrom->head->gene;
        Node *currentGene = chrom->tail;

        char selectedGene = smallestGene;

        while (currentGene != nullptr)
        {
            if (currentGene->gene < smallestGene)
            {
                selectedGene = currentGene->gene;
                break;
            }
            currentGene = currentGene->prev;
        }

        std::cout << selectedGene << " ";

        currentNode = currentNode->next;
    }

    std::cout << std::endl;
}
