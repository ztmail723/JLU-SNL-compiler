#ifndef LEXERIMP_H
#define LEXERIMP_H

#include "lexer.h"

class LexerImp : public Lexer
{
public:
    LexerImp();
    bool isKeyWord(QString str);//判断str是否为关键字
    LexType getLexType(QString str);//获取str对应的LexType
    TokenList* appendTokenList(TokenList* tokenlist, int _lineShow, LexType _lex, QString _sem);
    virtual TokenList* run(QString str) override;
};

#endif // LEXERIMP_H
