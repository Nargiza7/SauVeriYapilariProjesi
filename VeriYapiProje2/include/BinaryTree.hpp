#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP

#include "TreeNode.hpp"

const int MAX_WIDTH = 200;
const int MAX_HEIGHT = 20;

class BinaryTree
{
private:
    TreeNode *root;

    void preorderTraversal(TreeNode *node) const;
    void insert(TreeNode *&node, char value);
    void preorder(TreeNode *node) const;
    int calculateSum(TreeNode *node, bool isLeft) const;
    void clear(TreeNode *&node);
    void drawTreeHelper(TreeNode *node, int depth, int position, char lines[MAX_HEIGHT][MAX_WIDTH]) const;
    void mirror(TreeNode *node);
    TreeNode *findNode(TreeNode *node, char value);

public:
    BinaryTree();
    ~BinaryTree();
    void insert(char value);
    void displayPreorder() const;
    int calculateTreeSum() const;
    void drawTree() const;
    void preorderDraw() const;
    void mirrorSelectedNode(TreeNode *node);
    TreeNode *findNode(char value);
    TreeNode *getRoot() const;
	 
};

#endif
