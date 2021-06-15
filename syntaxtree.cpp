#include "syntaxtree.h"
#include "parserll1.h"
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

TreeNode::TreeNode(NodeKind nodekind, int lineno)
{
    for (int i = 0; i < 3; i ++)
        this->child[i] = nullptr;

    this->sibling = nullptr;
    this->lineno = lineno;
    this->nodekind = nodekind;
    this->idnum = 0;

    for (int i = 0; i < 10; i ++) {
        this->name[i] = "";
        this->table[i] = nullptr;
    }
}

TreeNode::~TreeNode()
{
    for (auto i : this->child)
    {
        delete i; //删除所有子结点
    }
}
