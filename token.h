#ifndef TOKEN_H
#define TOKEN_H
#include "global.h"
#include <QString>
class Token {
public:
    Token();
    void setLineShow(int lineShow);
    int& getLineShow();
    void setLexType(LexType lexType);
    LexType& getLexType();
    void setSem(QString sem);
    QString& getSem();

private:
    int lineShow; //记录该单词在源程序中的行数
    LexType lex; //记录该单词的词法信息
    QString sem; //记录该单词的语义信息
};

#endif // TOKEN_H
