#ifndef PARSER_H
#define PARSER_H

#include <QObject>
#include "tokenlist.h"
class Parser
{
public:
    Parser();
    TokenList run(QString code);
signals:

};

#endif // PARSER_H
