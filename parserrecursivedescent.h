#ifndef PARSERRECURSIVEDESCENT_H
#define PARSERRECURSIVEDESCENT_H

#include "parser.h"
#include "syntaxtree.h"
#include "global.h"

//递归下降法的语法分析程序
class ParserRecursiveDescent : public Parser
{
public:
    ParserRecursiveDescent();
    virtual SyntaxTree* run(TokenList tokenList) override;

private:
    bool match(LexType lexType);

    TreeNode* program();
    TreeNode* programHead();
    void programName(TreeNode* t);
    TreeNode* declarePart();
    TreeNode* typeDecpart();
    TreeNode* typeDec();
    TreeNode* typeDecList();
    TreeNode* typeDecMore();
    void typeID(TreeNode* t);
    void typeDef(TreeNode* t);
    void baseType(TreeNode* t);
    void structureType(TreeNode* t);
    void arrayType(TreeNode* t);
    void low(TreeNode* t);
    void top(TreeNode* t);
    void recType(TreeNode* t);
    TreeNode* fieldDecList();
    TreeNode* fieldDecMore();
    void idList(TreeNode* t);
    void idMore(TreeNode* t);
    TreeNode* varDecpart();
    TreeNode* varDec();
    TreeNode* varDecList();
    TreeNode* varDecMore();
    void varIDList(TreeNode* t);
    void varIDMore(TreeNode* t);
    TreeNode* procDecpart();
    TreeNode* procDec();
    TreeNode* procDecMore();
    void procName(TreeNode* t);
    void paramList(TreeNode* t);
    TreeNode* paramDecList();
    TreeNode* paramMore();
    TreeNode* param();
    void formList(TreeNode* t);
    void fidMore(TreeNode* t);
    TreeNode* procDecPart();
    TreeNode* procBody();
    TreeNode* programBody();
    TreeNode* stmList();
    TreeNode* stmMore();
    TreeNode* stm();
    TreeNode* assCall();
    TreeNode* assignmentRest();
    TreeNode* conditionalStm();
    TreeNode* loopStm();
    TreeNode* inputStm();
    void inVar(TreeNode* t);
    TreeNode* outputStm();
    TreeNode* returnStm();
    TreeNode* callStmRest();
    TreeNode* actParamList();
    TreeNode* actParamMore();
    TreeNode* relExp();
    TreeNode* exp();
    TreeNode* term();
    TreeNode* factor();
    TreeNode* variable();
    void variMore(TreeNode* t);
    TreeNode* fieldVar();
    void fieldVarMore(TreeNode* t);
    void cmpOp(TreeNode* t);
    void addOp(TreeNode* t);
    void multOp(TreeNode* t);

    void syntaxError(QString error);

private:
    TokenList tokenList;
    int cur;

    QString temp_name;
};

#endif // PARSERRECURSIVEDESCENT_H
