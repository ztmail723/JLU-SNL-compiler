#ifndef LEXER_H
#define LEXER_H
#include "tokenlist.h"

class Lexer
{
public:
    Lexer();
    virtual TokenList run(QString str) = 0;
};

#endif // LEXER_H
