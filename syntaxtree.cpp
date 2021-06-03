#include "syntaxtree.h"

SyntaxTree::SyntaxTree()
{
    root = nullptr;
}

SyntaxTree::~SyntaxTree()
{
    delete root;
}

void SyntaxTree::setRoot(TreeNode* node)
{
    this->root = node;
}

TreeNode* SyntaxTree::getRoot()
{
    return this->root;
}

TreeNode::~TreeNode()
{
    for (auto i : this->child)
    {
        delete i; //删除所有子结点
    }
}
