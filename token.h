#ifndef TOKEN_H
#define TOKEN_H
#include <QString>

enum class LexType
{
    /* 簿记单词符号 */
    ENDFILE, ERROR,
    /* 保留字 */
    PROGRAM, PROCEDURE, TYPE, VAR, IF,
    THEN, ELSE, FI, WHILE, DO, ENDWH,
    BEGIN, END1, READ, WRITE, ARRAY, OF,
    RECORD, RETURN1,
    /* 类型 */
    INTEGER, CHAR1,
    /* 多字符单词符号 */
    ID, INTC, CHARC,
    /* 特殊符号 */
    ASSIGN, EQ, LT, PLUS, MINUS,
    TIMES, OVER, LPAREN, RPAREN, DOT,
    COLON, SEMI, COMMA, LMIDPAREN, RMIDPAREN,
    UNDERANGE
};



class Token
{
public:
    Token();

private:
    int lineShow; //记录该单词在源程序中的行数
    LexType lex; //记录该单词的词法信息
    QString sem; //记录该单词的语义信息
};

#endif // TOKEN_H
