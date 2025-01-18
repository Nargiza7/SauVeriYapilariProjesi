/**
 * @file BinaryTree.cpp
 * @description Bağlı Liste ile İkili Arama Ağaçlarının Yönetimi
 * @course Veri Yapilari 2-B
 * @assignment 2.Ödev
 * @date 25.12.2024
 * @author Nargiza Zhyrgalbek Kyzy nargiza.kyzy@ogr.sakarya.edu.tr
 */
 
#include "BinaryTree.hpp"
#include "TreeNode.hpp"
#include <iostream>
#include <cstring>

BinaryTree::BinaryTree() : root(nullptr) {}

BinaryTree::~BinaryTree()
{
    clear(root);
}

void BinaryTree::preorderDraw() const
{
    preorderTraversal(root);
}

void BinaryTree::preorderTraversal(TreeNode *node) const
{
    if (node == nullptr)
        return;

    std::cout << node->data << " ";
    preorderTraversal(node->left);
    preorderTraversal(node->right);
}

void BinaryTree::insert(TreeNode *&node, char value)
{
    if (node == nullptr)
    {
        node = new TreeNode(value);
    }
    else if (value < node->data)
    {
        insert(node->left, value);
    }
    else if (value > node->data)
    {
        insert(node->right, value);
    }
}

void BinaryTree::insert(char value)
{
    insert(root, value);
}

void BinaryTree::preorder(TreeNode *node) const
{
    if (node)
    {
        std::cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }
}

void BinaryTree::displayPreorder() const
{
    preorder(root);
    std::cout << std::endl;
}

int BinaryTree::calculateSum(TreeNode *node, bool isLeft) const
{
    if (!node)
        return 0;

    int value = (int)(node->data);
    if (isLeft)
        value *= 2;

    return value + calculateSum(node->left, true) + calculateSum(node->right, false);
}

int BinaryTree::calculateTreeSum() const
{
    return calculateSum(root, false);
}

void BinaryTree::clear(TreeNode *&node)
{
    if (node)
    {
        clear(node->left);
        clear(node->right);
        delete node;
        node = nullptr;
    }
}

 void BinaryTree::drawTreeHelper(TreeNode *node, int depth, int position, char lines[MAX_HEIGHT][MAX_WIDTH]) const
{
    if (!node || depth >= MAX_HEIGHT || position < 0 || position >= MAX_WIDTH)
        return;
	
 //   lines[depth++][position] = '.';
	lines[depth][position] = '.';
	
	lines[depth + 1][position] = node->data;

    // Sol alt ağaç
    if (node->left)
    {
        int leftPos = std::max(0, position - (32 >> depth) - 3);
        if (leftPos >= 0)
        {

            for (int i = position - 1; i > leftPos; --i)
            {
                lines[depth + 1][i] = '.';
            }
            lines[depth + 2][leftPos] = '.';
        }
        drawTreeHelper(node->left, depth + 1, leftPos, lines);
    }

    // Sağ alt ağaç
    if (node->right)
    {
        int rightPos = std::min(MAX_WIDTH - 1, position + (32 >> depth) + 3); // 3 boşluk bırakıyoruz
        if (rightPos < MAX_WIDTH)
        {
            // Sağ bağlantı çizgisi
            for (int i = position + 1; i < rightPos; ++i)
            {
                lines[depth + 1][i] = '.';
            }
            lines[depth + 2][rightPos] = '.';
        }
        drawTreeHelper(node->right, depth + 1, rightPos, lines);
    }
} 
 
void BinaryTree::drawTree() const
{
    char lines[MAX_HEIGHT][MAX_WIDTH];

    for (int i = 0; i < MAX_HEIGHT; ++i)
    {
        std::memset(lines[i], ' ', MAX_WIDTH - 1);
        lines[i][MAX_WIDTH - 1] = '\0';
    }

    // Ağaç çizimini başlat
    drawTreeHelper(root, 0, MAX_WIDTH / 2, lines);

    // Çizimi yazdır
    for (int i = 0; i < MAX_HEIGHT; ++i)
    {
        bool hasContent = false;
        for (int j = 0; j < MAX_WIDTH; ++j)
        {
            if (lines[i][j] != ' ')
            {
                hasContent = true;
                break;
            }
        }

        if (hasContent)
        {
            std::cout << lines[i] << std::endl;
        }
    }
}

void BinaryTree::mirror(TreeNode *node)
{
    if (node == nullptr)
        return;

    TreeNode *temp = node->left;
    node->left = node->right;
    node->right = temp;

    mirror(node->left);
    mirror(node->right);
}

void BinaryTree::mirrorSelectedNode(TreeNode *node)
{
    if (node == nullptr)
        return;
    mirror(node);
}

TreeNode *BinaryTree::findNode(TreeNode *node, char value)
{
    if (node == nullptr)
        return nullptr;

    if (node->data == value)
        return node;
    if (value < node->data)
        return findNode(node->left, value);
    return findNode(node->right, value);
}

TreeNode *BinaryTree::findNode(char value)
{
    return findNode(root, value);
}

TreeNode *BinaryTree::getRoot() const
{
    return root;
}