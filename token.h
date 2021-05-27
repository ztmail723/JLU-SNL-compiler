#ifndef TOKEN_H
#define TOKEN_H

#include <QObject>

class Token : public QObject
{
    Q_OBJECT
public:
    explicit Token(QObject *parent = nullptr);

signals:

};

#endif // TOKEN_H
