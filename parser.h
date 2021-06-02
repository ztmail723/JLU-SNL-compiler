#ifndef PARSER_H
#define PARSER_H

#include <QObject>
#include "tokenlist.h"
#include "syntaxtree.h"
class Parser
{
public:
    Parser();
    virtual SyntaxTree run(TokenList tokenList) = 0;
};

#endif // PARSER_H
