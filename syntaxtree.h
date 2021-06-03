#ifndef SYNTAXTREE_H
#define SYNTAXTREE_H
#include "global.h"
#include "token.h"
#include <QVector>

class TreeNode
{
public:
    QVector<TreeNode*> child; // 指向子语法树结点指针
    TreeNode* sibling; // 指向兄弟语法树结点指针
    int lineno; // 记录源程序行号
    NodeKind nodekind; // 记录语法树的结点类型
    Kind kind; // 记录语法树结点的具体类型，为共用体结构
    int idnum; // 记录一个结点中标识符的个数
    QVector<QString> name; // 结点中标识符的名字
    QVector<Symbtable*> table; // 指针数组，数组成员是结点中各个标识符在符号表中的入口
    QString type_name; // 记录类型名，当结点是声明类型，且类型是由类型标识符表示时有效
    struct
    {
        struct
        {
            int low; // 整型类型变量，记录数组的下界
            int up; // 整型类型变量，记录数组的上界
            DecKind childtype; // 记录数组的成员类型
        } ArrayAttr; // 记录数组类型的属性
        struct
        {
            ParamType paramt; // 记录过程的参数类型，表示过程的参数是值参或变参
        } ProcAttr; // 记录过程的属性
        struct
        {
            LexType op; // 记录语法树结点的运算符单词，为单词类型。
            // 当语法树结点为"关系运算表达式"对应结点时，取值LT、EQ
            // 当语法树结点为"加法运算简单表达式"对应结点时，取值PLUS、MINUS
            // 当语法树结点为"乘法运算项"对应结点时，取值TIMES、OVER
            // 其余情况下无效
            int val; // 记录语法树结点的数值，当语法树结点为"数字因子"对应的语法树结点时有效，为整数类型
            VarKind varkind;
            ExpType type; // 记录语法树结点的检查类型，取值Void, Integer, Boolean, 为类型检查ExpType类型
        } ExpAttr; // 记录表达式的属性
    } attr;
    ~TreeNode();
};

class SyntaxTree
{
public:
    SyntaxTree();
    ~SyntaxTree();
    void setRoot(TreeNode* node);
    TreeNode* getRoot();
private:
    TreeNode* root;
};

#endif // SYNTAXTREE_H
