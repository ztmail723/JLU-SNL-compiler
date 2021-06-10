#ifndef PARSERLL1_H
#define PARSERLL1_H

#include "parser.h"
#include <QStack>

class ParserLL1 : public Parser
{
public:
    ParserLL1();
    virtual SyntaxTree* run(TokenList tokenList) override;
private:
    QMap<QPair<LexType, LexType>, int> table;
    QStack<LexType> symbal_stack;
    QStack<TreeNode**> syntaxtree_stack;
    QStack<TreeNode*> op_stack;
    QStack<TreeNode*> num_stack;

    TreeNode* current_treenode;
    Token* head;
    DecKind* temp;
    TreeNode* saveP;
    bool getExpResult = true;
    int expflag = 0;
    int getExpResult2 = false;
public:
    static int nowLine;
    static TreeNode* newSpecNode(NodeKind kind);
    static TreeNode* newStmtNode(StmtKind kind);
    static TreeNode* newExpNode(ExpKind kind);
private:
    int getPriosity(LexType op);
    void process(int id);
};

#endif // PARSERLL1_H
