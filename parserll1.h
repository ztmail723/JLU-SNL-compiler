#ifndef PARSERLL1_H
#define PARSERLL1_H

#include "parser.h"

class ParserLL1 : public Parser {
public:
    ParserLL1();
    virtual SyntaxTree run(TokenList tokenList) override;
};

#endif // PARSERLL1_H
