#ifndef TOKENLIST_H
#define TOKENLIST_H

#include <QObject>
#include <QVector>
#include "token.h"

class TokenList
{
public:
    TokenList();
    void append(Token& token);//添加元素
    void remove(int index);//删除元素
    Token& operator[](int index);
    int size();
private:
    QVector<Token> tokenList;
};

#endif // TOKENLIST_H
