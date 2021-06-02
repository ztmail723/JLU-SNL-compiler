#ifndef PARSERRECURSIVEDESCENT_H
#define PARSERRECURSIVEDESCENT_H

#include "parser.h"

//递归下降法的语法分析程序
class ParserRecursiveDescent : public Parser
{
public:
    ParserRecursiveDescent();
    virtual SyntaxTree run(TokenList tokenList) override;
};

#endif // PARSERRECURSIVEDESCENT_H
