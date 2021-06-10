#include "tokenlist.h"

TokenList::TokenList()
{

}

void TokenList::append(Token& token)
{
    this->tokenList.append(token);
}

void TokenList::remove(int index)
{
    this->tokenList.erase(this->tokenList.begin() + index);
}

Token& TokenList::operator[](int index)
{
    return this->tokenList[index];
}

int TokenList::size()
{
    return this->tokenList.size();
}
