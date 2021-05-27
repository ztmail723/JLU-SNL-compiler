#ifndef LEXER_H
#define LEXER_H

#include <QObject>

class Lexer : public QObject
{
    Q_OBJECT
public:
    explicit Lexer(QObject *parent = nullptr);

signals:

};

#endif // LEXER_H
