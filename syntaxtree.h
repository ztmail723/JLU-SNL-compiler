#ifndef SYNTAXTREE_H
#define SYNTAXTREE_H
#include <QVector>

class SyntaxTree
{
public:
    class TreeNode
    {
    public:
        QVector<TreeNode*> child; // 指向子语法树结点指针，容量为3
        TreeNode* sibling; // 指向兄弟语法树结点指针
        int lineno; //记录源程序行号
    };
    SyntaxTree();
};

#endif // SYNTAXTREE_H
