#ifndef PARSER_H
#define PARSER_H

#include <QObject>
#include "tokenlist.h"
class Parser : public QObject
{
    Q_OBJECT
public:
    explicit Parser(QObject* parent = nullptr);
    TokenList run(QString code);
signals:

};

#endif // PARSER_H
