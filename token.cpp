#include "token.h"

Token::Token()
{

}

void Token::setLineShow(int lineShow)
{
    this->lineShow = lineShow;
}

int& Token::getLineShow()
{
    return this->lineShow;
}

void Token::setLexType(LexType lexType)
{
    this->lex = lexType;
}

LexType& Token::getLexType()
{
    return this->lex;
}

void Token::setSem(QString sem)
{
    this->sem = sem;
}

QString& Token::getSem()
{
    return this->sem;
}
