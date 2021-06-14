#ifndef LEXERIMP_H
#define LEXERIMP_H

#include "lexer.h"
#include <QQueue>

class LexerImp : public Lexer
{
public:
    int k=0;
    LexerImp();
    bool isKeyWord(QString str);//判断str是否为关键字
    LexType getLexType(QString str);//获取str对应的LexType
    TokenList* appendTokenList(TokenList* tokenlist, int _lineShow, LexType _lex, QString _sem);
    int getCharType(QChar c);
    QList<QString> pushString(QList<QString> strQueue, QString str);
    TokenList* queueToList(TokenList* tokenList, QList<QString> strQueue);
    virtual TokenList* run(QString str) override;
    virtual TokenList* run1(QString str) override;
};

#endif // LEXERIMP_H
