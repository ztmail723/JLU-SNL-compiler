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

TreeNode* TreeNode::newSpecNode(NodeKind kind)
{
    auto t = new TreeNode;
    int i;
    for (i = 0; i < 3; i++)
    {
        t->child.append(nullptr);
    }
    t->sibling = nullptr;
    t->nodekind = kind;
    //t->lineno = lineno;
    t->lineno = 1;
    t->idnum = 0;
    for (i = 0; i < 10; i++)
    {
        t->table[i] = nullptr;
    }
    return t;
}
