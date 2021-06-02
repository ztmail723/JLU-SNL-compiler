#ifndef PARSER_H
#define PARSER_H

#include "syntaxtree.h"
#include "tokenlist.h"
#include <QObject>
class Parser {
public:
    Parser();
    virtual ~Parser() = default;
    virtual SyntaxTree run(TokenList tokenList) = 0;
};

#endif // PARSER_H
