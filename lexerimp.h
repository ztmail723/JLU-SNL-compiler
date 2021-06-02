#ifndef LEXERIMP_H
#define LEXERIMP_H

#include "lexer.h"

class LexerImp : public Lexer {
public:
    LexerImp();
    virtual TokenList run(QString str) override;
};

#endif // LEXERIMP_H
