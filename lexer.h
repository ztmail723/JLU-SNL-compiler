#ifndef LEXER_H
#define LEXER_H
#include "tokenlist.h"
#include <QStack>

class Lexer
{
public:
    Lexer();
    virtual ~Lexer() = default;
    virtual TokenList* run(QString str) = 0;
    virtual TokenList* run1(QString str) = 0;
};

#endif // LEXER_H
