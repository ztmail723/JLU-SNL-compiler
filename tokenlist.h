#ifndef TOKENLIST_H
#define TOKENLIST_H

#include <QVector>
#include "token.h"

class TokenList
{
public:
    TokenList();
    void append(Token& token);//添加元素
    void remove(int index);//删除元素
    Token& operator[](int index);//获取元素
    int size();//获取元素个数
private:
    QVector<Token> tokenList;
};

#endif // TOKENLIST_H
