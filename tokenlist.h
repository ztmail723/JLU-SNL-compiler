#ifndef TOKENLIST_H
#define TOKENLIST_H

#include <QObject>
#include <QVector>
#include "token.h"

class TokenList : public QObject
{
    Q_OBJECT
public:
    explicit TokenList(QObject* parent = nullptr);

private:
    QVector<Token> tokenList;

signals:

};

#endif // TOKENLIST_H
