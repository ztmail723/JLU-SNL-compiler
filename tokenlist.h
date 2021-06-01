#ifndef TOKENLIST_H
#define TOKENLIST_H

#include <QObject>
#include <QVector>
#include "token.h"

class TokenList
{
public:
    TokenList();
    void add(Token& token);
    void del(int index);
    Token get(int index);
private:
    QVector<Token> tokenList;

signals:

};

#endif // TOKENLIST_H
