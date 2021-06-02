#ifndef PARSER_H
#define PARSER_H

#include <QObject>
#include "tokenlist.h"
class Parser
{
public:
    Parser();
    virtual TokenList run(TokenList tokenList) = 0;
};

#endif // PARSER_H
