/**
 * @file main.cpp
 * @description Bagli Liste ile Gen Kromozom ve DNA Projesi
 * @course Veri Yapilari 2-B
 * @assignment 1.Ödev
 * @date 26.11.2024
 * @author Nargiza Zhyrgalbek Kyzy nargiza.kyzy@ogr.sakarya.edu.tr
 */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <limits>
#include "DNA.hpp"
#include "Chromosome.hpp"

void displayMenu()
{
    std::cout << "1- Caprazlama\n";
    std::cout << "2- Mutasyon\n";
    std::cout << "3- Otomatik Islemler\n";
    std::cout << "4- Ekrana Yaz\n";
    std::cout << "5- Cikis\n";
    std::cout << "Seciminizi yapin: ";
}

int main()
{
    DNA dna;
    std::ifstream file("Dna.txt");

    if (!file.is_open())
    {
        std::cerr << "Dna.txt dosyasi acilamadi!" << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(file, line))
    {
        Chromosome *chromosome = new Chromosome();
        std::istringstream iss(line);
        char gene;

        while (iss >> gene)
        {
            chromosome->addGene(gene);
        }

        dna.addChromosome(chromosome);
    }
    file.close();

    int choice;
    do
    {
        displayMenu();

        if (!(std::cin >> choice))
        {
            std::cout << "Gecersiz bir karakter veya sembol girdiniz. Lutfen tekrar deneyin.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        switch (choice)
        {
        case 1:
        {
            // Çaprazlama işlemi
            int index1, index2;
            std::cout << "Caprazlamak icin ilk kromozom satir numarasi giriniz (0'dan baslar): ";
            std::cin >> index1;
            std::cout << "Caprazlamak icin ikinci kromozom satir numarasi giriniz (0'dan baslar): ";
            std::cin >> index2;

            dna.crossOver(index1, index2);
			
			std::cout << "Caprazlama islemi basarili!" << std::endl;
            break;
        }
        case 2:
        {
            // Mutasyon işlemi
            int chromIndex, geneIndex;
            std::cout << "Mutasyon icin kromozom satir numarasini girin: ";
            std::cin >> chromIndex;
            std::cout << "Mutasyon icin gen sutun numarasini girin: ";
            std::cin >> geneIndex;

            dna.mutate(chromIndex, geneIndex); // Mutasyon işlemi

            //std::cout << "Guncellenmis DNA:" << std::endl;
            //std::cout << dna;
			std::cout << "Mutasyon islemi basarili!" << std::endl;
            break;
        }
        case 3:
        {
            // Otomatik işlemler
            std::ifstream operationsFile("Islemler.txt");
            if (!operationsFile.is_open())
            {
                std::cerr << "Islemler.txt dosyasi acilamadi!" << std::endl;
                break;
            }
            std::string line;
            while (std::getline(operationsFile, line))
            {
                std::istringstream iss(line);
                char operation;
                int index1, index2;

                iss >> operation;
                if (operation == 'C')
                {
                    // Çaprazlama işlemi
                    iss >> index1 >> index2;
                    dna.crossOver(index1, index2);
                }
                else if (operation == 'M')
                {
                    // Mutasyon işlemi
                    iss >> index1 >> index2;
                    dna.mutate(index1, index2);
                }
            }

            operationsFile.close();
            std::cout << "Islemler tamamlandi!" << std::endl;
            break;
        }
        case 4:
        {
            // Ekrana yazdırma
            std::cout << "\nEkrana Yazma Islemi Sonuclari:\n";
            dna.writeToScreen();
            break;
        }
        case 5:
        {
            // Çıkış
            std::cout << "Cikiliyor...\n";
            break;
        }
        default:
            std::cout << "Gecersiz secenek. Lutfen 1 ile 5 arasinda bir secim yapin.\n";
        }
    } while (choice != 5);

    while (std::getline(file, line))
    {
        Chromosome *chromosome = new Chromosome();
        std::istringstream iss(line);
        char gene;

        while (iss >> gene)
        {
            chromosome->addGene(gene);
        }

        dna.addChromosome(chromosome);
    }

    return 0;
}
