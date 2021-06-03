#include "global.h"
QMap<LexType, QString> ConstantVar::lexName = { { LexType::PROGRAM, "PROGRAM" },
    { LexType::TYPE, "TYPE" }, { LexType::VAR, "VAR" },
    { LexType::PROCEDURE, "PROCEDURE" }, { LexType::BEGIN, "BEGIN" },
    { LexType::END, "END" }, { LexType::ARRAY, "ARRAY" },
    { LexType::OF, "OF" }, { LexType::RECORD, "RECORD" },
    { LexType::IF, "IF" }, { LexType::THEN, "THEN" },
    { LexType::ELSE, "ELSE" }, { LexType::FI, "FI" },
    { LexType::WHILE, "WHILE" }, { LexType::DO, "DO" },
    { LexType::ENDWH, "ENDWH" }, { LexType::READ, "READ" },
    { LexType::WRITE, "WRITE" }, { LexType::RETURN, "RETURN" },
    { LexType::INTEGER_T, "INTEGER_T" }, { LexType::CHAR_T, "CHAR_T" },
    { LexType::ID, "ID" }, { LexType::INTC_VAL, "INTC_VAL" },
    { LexType::CHARC_VAL, "CHAR_VAL" }, { LexType::ASSIGN, ":=" },
    { LexType::EQ, "=" }, { LexType::LT, "<" },
    { LexType::PLUS, "+" }, { LexType::MINUS, "-" },
    { LexType::TIMES, "*" }, { LexType::DIVIDE, "/" },
    { LexType::LPAREN, "(" }, { LexType::RPAREN, ")" },
    { LexType::DOT, "." }, { LexType::COLON, ":" },
    { LexType::SEMI, ";" }, { LexType::COMMA, "," },
    { LexType::LMIDPAREN, "[" }, { LexType::RMIDPAREN, "]" },
    { LexType::UNDERANGE, ".." }, { LexType::ENDFILE, "EOF" },
    { LexType::ERROR, "ERROR" }
};
QMap<QString, LexType> ConstantVar::reservedWords = { { "program", LexType::PROGRAM },
    { "type", LexType::TYPE },
    { "var", LexType::VAR },
    { "procedure", LexType::PROCEDURE },
    { "begin", LexType::BEGIN },
    { "end", LexType::END },
    { "array", LexType::ARRAY },
    { "of", LexType::OF },
    { "record", LexType::RECORD },
    { "if", LexType::IF },
    { "then", LexType::THEN },
    { "else", LexType::ELSE },
    { "fi", LexType::FI },
    { "char", LexType::CHAR_T },
    { "while", LexType::WHILE },
    { "do", LexType::DO },
    { "endwh", LexType::ENDWH },
    { "read", LexType::READ },
    { "write", LexType::WRITE },
    { "return", LexType::RETURN },
    { "integer", LexType::INTEGER_T }
};
QMap<char, LexType> ConstantVar::opWords = { { '+', LexType::PLUS }, { '-', LexType::MINUS }, { '*', LexType::TIMES },
    { '/', LexType::DIVIDE }, { '(', LexType::LPAREN }, { ')', LexType::RPAREN },
    { ';', LexType::SEMI }, { '[', LexType::LMIDPAREN }, { ']', LexType::RMIDPAREN },
    { '=', LexType::EQ }, { '<', LexType::LT }, { ',', LexType::COMMA },
    { EOF, LexType::ENDFILE }
};
QMap<NodeKind, QString> ConstantVar::nodekindName = {{NodeKind::ProK, "ProK"},
    {NodeKind::PheadK, "PheadK"},
    {NodeKind::TypeK, "TypeK"},
    {NodeKind::VarK, "VarK"},
    {NodeKind::ProcDecK, "ProcDecK"},
    {NodeKind::StmLK, "StmLK"},
    {NodeKind::DecK, "DecK"},
    {NodeKind::StmtK, "StmtK"},
    {NodeKind::ExpK, "ExpK"}
};
