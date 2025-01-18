/**
 * @file main.cpp
 * @description Bağlı Liste ile İkili Arama Ağaçlarının Yönetimi
 * @course Veri Yapilari 2-B
 * @assignment 2.Ödev
 * @date 25.12.2024
 * @author Nargiza Zhyrgalbek Kyzy nargiza.kyzy@ogr.sakarya.edu.tr
 */

#include "LinkedList.hpp"
#include "BinaryTree.hpp"
#include <fstream>
#include <string>
#include <iostream>
#include <cstdlib>

void clearConsole()
{
#ifdef _WIN32
    system("cls");
#endif
}

#ifdef _WIN32
#include <windows.h>

void MaximizeConsoleWindow()
{
    HWND consoleWindow = GetConsoleWindow();
    if (consoleWindow == nullptr)
    {
        std::cerr << "Konsol penceresinin handle'i alinamadi!" << std::endl;
        return;
    }

    ShowWindow(consoleWindow, SW_MAXIMIZE);
}

#endif

LinkedList readFile(const std::string &filename);

int myMin(int a, int b)
{
    return (a < b) ? a : b;
}

int main()
{
    MaximizeConsoleWindow();
    // Dosyadan ağaçları oku
    LinkedList list = readFile("agaclar.txt");

    int toplamDugum = list.NodeCount();
    int currentIndex = 0;
    const int pageSize = 10;
    char command;

    if (toplamDugum == 0)
    {
        std::cerr << "Dosyada agac bulunamadi veya liste bos." << std::endl;
        return 1;
    }

    int currentPageStart = 0;
    // list.display(currentPageStart, std::min(pageSize, toplamDugum));
    list.display(currentPageStart, myMin(pageSize, toplamDugum));

    list.displayWithIndicator(currentIndex, pageSize);

    while (true)
    {
        clearConsole();

        currentPageStart = (currentIndex / pageSize) * pageSize;
        list.display(currentPageStart, std::min(pageSize, toplamDugum - currentPageStart));
        list.displayWithIndicator(currentIndex, pageSize);

        Node *currentNode = list.getNodeAt(currentIndex);
        if (currentNode != nullptr)
        {
            std::cout << "\nAktif agacin yapisi (Dugum " << currentIndex + 1 << "):\n";
            currentNode->tree->drawTree();
        }
        else
        {
            std::cout << "\nAktif agac bulunamadi." << std::endl;
        }
        char command;
        std::cout << "a-A - Sola Git\n";
        std::cout << "d-D - Saga Git\n";
        std::cout << "s-S - Silme Islemi\n";
        std::cout << "w-W - Aynalama Islemi\n";
        std::cout << "q-Q - Cikis\n";
        std::cout << "Seciminizi yapin: ";
        std::cin >> command;

        if (command == 'D' || command == 'd')
        {
            if (currentIndex + 1 < toplamDugum)
            {
                currentIndex++;
                if (currentIndex >= currentPageStart + pageSize)
                {
                    currentPageStart += pageSize;
                    currentIndex = currentPageStart;
                }
            }
            else
            {
                std::cout << "Son dugumde bulunuyorsunuz!" << std::endl;
            }
        }
        else if (command == 'A' || command == 'a')
        {
            if (currentIndex > 0)
            {
                currentIndex--;
                if (currentIndex < currentPageStart)
                {
                    currentPageStart -= pageSize;
                    currentIndex = currentPageStart + pageSize - 1;
                }
            }
            else
            {
                std::cout << "Ilk dugumde bulunuyorsunuz!" << std::endl;
            }
        }
        else if (command == 'S' || command == 's')
        {

            if (toplamDugum > 0)
            {
                list.remove(currentIndex);
                toplamDugum--;

                if (currentIndex >= toplamDugum)
                {
                    currentIndex = toplamDugum - 1;
                }
            }
            else
            {
                std::cout << "Silinecek dugum bulunmuyor!" << std::endl;
            }
        }
        else if (command == 'W' || command == 'w')
        {
            if (currentNode != nullptr && currentNode->tree != nullptr)
            {
                std::cout << "Aktif agac aynalaniyor..." << std::endl;
                currentNode->tree->mirrorSelectedNode(currentNode->tree->getRoot());
                std::cout << "Aynalama islemi tamamlandi!" << std::endl;
            }
            else
            {
                std::cout << "Aynalama islemi yapilacak agac bulunamadi!" << std::endl;
            }
        }
        else if (command == 'Q' || command == 'q')
        {
            while (toplamDugum > 0)
            {
                list.remove(currentIndex);
                toplamDugum--;

                if (currentIndex >= toplamDugum)
                {
                    currentIndex = toplamDugum - 1;
                }
            }
            clearConsole();
            break;
        }
        else
        {
            std::cout << "Gecersiz komut!" << std::endl;
        }
    }

    return 0;
}

LinkedList readFile(const std::string &filename)
{
    LinkedList list;
    std::ifstream file(filename);

    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            BinaryTree *tree = new BinaryTree();
            for (char c : line)
            {
                tree->insert(c);
            }
            list.add(tree);
        }
        file.close();
    }
    else
    {
        std::cerr << "Dosya acilamadi: " << filename << std::endl;
    }

    return list;
}
