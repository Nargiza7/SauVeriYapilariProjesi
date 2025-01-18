/**
 * @file LinkedList.cpp
 * @description Bağlı Liste ile İkili Arama Ağaçlarının Yönetimi
 * @course Veri Yapilari 2-B
 * @assignment 2.Ödev
 * @date 25.12.2024
 * @author Nargiza Zhyrgalbek Kyzy nargiza.kyzy@ogr.sakarya.edu.tr
 */
#include "LinkedList.hpp"
#include <iomanip>
#include <iostream>

LinkedList::LinkedList() : head(nullptr), tail(nullptr), current(nullptr) {}

LinkedList::~LinkedList()
{
    Node *current = head;
    while (current != nullptr)
    {
        Node *temp = current;
        delete current->tree; // BinaryTree nesnesini sil
        current = current->next;
        delete temp; // Node'u sil
    }
}

void LinkedList::remove(int index)
{
    if (index < 0 || index >= NodeCount())
        return;

    Node *current = head;
    Node *previous = nullptr;

    if (index == 0)
    {
        head = current->next;
        delete current;
        return;
    }

    for (int i = 0; current != nullptr && i < index; i++)
    {
        previous = current;
        current = current->next;
    }
	

    if (current == nullptr)
        return;

    previous->next = current->next;
    delete current;
}

void LinkedList::add(BinaryTree *tree)
{
    Node *newNode = new Node(tree);
    if (!head)
    {
        head = newNode;
        tail = newNode;
        current = head;
    }
    else
    {
        tail->next = newNode;
        tail = newNode;
		tail->next = nullptr;
    }
}

 void LinkedList::display(int start, int count) const
{
    Node *temp = head;
	
    for (int i = 0; i < start && temp; i++)
    {
        temp = temp->next;
    }
	
    int printedNodes = 0;

    for (int i = 0; i < count && temp; i++, printedNodes++)
    {
        std::cout << "..............  ";
        temp = temp->next;
    }
    std::cout << "\n";

    temp = head;
    for (int i = 0; i < start && temp; i++)
    {
        temp = temp->next;
    }
    for (int i = 0; i < count && temp; i++)
    {
        std::cout << ".  " << std::setw(10) << (int)temp << ".  ";
        temp = temp->next;
    }
    std::cout << "\n";

    temp = head;
    for (int i = 0; i < printedNodes; i++)
    {

        std::cout << "..............  ";
    }
    std::cout << "\n";

    temp = head;
    for (int i = 0; i < start && temp; i++)
    {
        temp = temp->next;
    }
    for (int i = 0; i < count && temp; i++)
    {
        std::cout << ". " << std::setw(10) << temp->tree->calculateTreeSum() << " .  ";
        temp = temp->next;
    }
    std::cout << "\n";

    temp = head;
    for (int i = 0; i < printedNodes; i++)
    {
        std::cout << "..............  ";
    }
    std::cout << "\n";

    temp = head;
    for (int i = 0; i < start && temp; i++)
    {
        temp = temp->next;
    }
    for (int i = 0; i < count && temp; i++)
    {
        if (temp->next == nullptr)
        {
            std::cout << ".        NULL.";
        }
        else
        {
            std::cout << ".  " << std::setw(10) << (int)temp->next << ".  ";
        }
        temp = temp->next;
    }
    std::cout << "\n";

    temp = head;
    for (int i = 0; i < printedNodes; i++)
    {
        std::cout << "..............  ";
    }
    std::cout << "\n";
} 

void LinkedList::displayWithIndicator(int currentIndex, int pageSize) const
{
    Node *temp = head;
    int index = 0;

    temp = head;
    while (temp)
    {
        if (index == currentIndex % pageSize)
        {
            std::cout << "^^^^^^^^^^^^^^";
			break;
        }
        else
        {
            std::cout << "                ";
        }
        temp = temp->next;
        index++;
    }
    std::cout << "\n";

    temp = head;
    index = 0;
    while (temp)
    {
        if (index == currentIndex % pageSize)
        {
            std::cout << "||||||||||||||";
			break;
        }
        else
        {
            std::cout << "                ";
        }
        temp = temp->next;
        index++;
    }
    std::cout << "\n";
}

int LinkedList::NodeCount() const
{
    int count = 0;
    Node *current = head;
    while (current)
    {
        count++;
        current = current->next;
    }
    return count;
}

Node *LinkedList::getNodeAt(int index) const
{
    Node *temp = head;
    int currentIndex = 0;

    while (temp != nullptr && currentIndex < index)
    {
        temp = temp->next;
        currentIndex++;
    }

    return temp;
}
