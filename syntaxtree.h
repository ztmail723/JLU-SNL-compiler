#ifndef SYNTAXTREE_H
#define SYNTAXTREE_H
#include <QVector>

enum class NodeKind
{
    ProK,
    PheadK,
    TypeK,
    VarK,
    ProcDecK,
    StmLK,
    DecK,
    StmtK,
    ExpK
};
enum class DecKind
{
    ArrayK,
    CharK,
    IntegerK,
    RecordK,
    IdK
};
enum class StmtKind
{
    IfK,
    WhileK,
    AssignK,
    ReadK,
    WriteK,
    CallK,
    ReturnK
};
enum class ExpKind
{
    OpK,
    ConstK,
    IdK
};
union Kind
{
    DecKind dec;
    StmtKind stmt;
    ExpKind exp;
};

class TreeNode
{
public:
    QVector<TreeNode*> child; // 指向子语法树结点指针
    TreeNode* sibling; // 指向兄弟语法树结点指针
    int lineno; //记录源程序行号
    NodeKind nodekind; //记录语法树的结点类型
    Kind kind; //记录语法树结点的具体类型，为共用体结构
    int idnum; //记录一个结点中标识符的个数
    QString name; //结点中标识符的名字
};


class SyntaxTree
{
public:
    SyntaxTree();
};

#endif // SYNTAXTREE_H
