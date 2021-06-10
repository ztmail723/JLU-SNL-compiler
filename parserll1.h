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
    int getPriosity(LexType op);
};

#endif // PARSERLL1_H
