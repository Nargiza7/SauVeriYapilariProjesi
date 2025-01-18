/**
 * @file FileReader.cpp
 * @description Bağlı Liste ile İkili Arama Ağaçlarının Yönetimi
 * @course Veri Yapilari 2-B
 * @assignment 2.Ödev
 * @date 25.12.2024
 * @author Nargiza Zhyrgalbek Kyzy nargiza.kyzy@ogr.sakarya.edu.tr
 */
 
#include "FileReader.hpp"
#include <fstream>
#include <iostream>

LinkedList FileReader::readFromFile(const std::string &filename)
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
