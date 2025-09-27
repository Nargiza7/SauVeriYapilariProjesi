/**
 * @file Node.cpp
 * @description Bagli Liste ile Gen Kromozom ve DNA Projesi
 * @course Veri Yapilari 2-B
 * @assignment 1.Ödev
 * @date 26.11.2024
 * @author Nargiza Zhyrgalbek Kyzy nargiza.kyzy@ogr.sakarya.edu.tr
 */

#include "Node.hpp"

Node::Node() : gene('\0'), next(nullptr) {}
Node::Node(char g) : gene(g), next(nullptr), prev(nullptr) {}
