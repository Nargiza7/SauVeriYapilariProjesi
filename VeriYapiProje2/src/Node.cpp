/**
 * @file Node.cpp
 * @description Bağlı Liste ile İkili Arama Ağaçlarının Yönetimi
 * @course Veri Yapilari 2-B
 * @assignment 2.Ödev
 * @date 25.12.2024
 * @author Nargiza Zhyrgalbek Kyzy nargiza.kyzy@ogr.sakarya.edu.tr
 */

#include "Node.hpp"

Node::Node(BinaryTree *t) : tree(t), next(nullptr) {}
Node::~Node() { delete tree; }
