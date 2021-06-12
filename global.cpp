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

std::set<LexType> ConstantVar::TTSet =
{
    // 簿记单词符号
    LexType::ENDFILE,   LexType::ERROR,
    // 保留字
    LexType::PROGRAM,   LexType::PROCEDURE, LexType::TYPE,  LexType::VAR,       LexType::IF,
    LexType::THEN,      LexType::ELSE,      LexType::FI,        LexType::WHILE,     LexType::DO,
    LexType::ENDWH,     LexType::BEGIN,     LexType::END,   LexType::READ,      LexType::WRITE,
    LexType::ARRAY,     LexType::OF,        LexType::RECORD,    LexType::RETURN,
    LexType::INTEGER_T, LexType::CHAR_T,
    // 多字符单词符号
    LexType::ID,        LexType::INTC_VAL,      LexType::CHARC_VAL,
    // 特殊符号
    LexType::ASSIGN,        LexType::EQ,        LexType::LT,        LexType::PLUS,      LexType::MINUS,
    LexType::TIMES, LexType::DIVIDE,        LexType::LPAREN,    LexType::RPAREN,        LexType::DOT,
    LexType::COLON,     LexType::SEMI,      LexType::COMMA, LexType::LMIDPAREN, LexType::RMIDPAREN,
    LexType::UNDERANGE
};
std::set<LexType> ConstantVar::NTSet =
{
    LexType::Program,         LexType::ProgramHead,     LexType::ProgramName,   LexType::DeclarePart,
    LexType::TypeDec,        LexType::TypeDeclaration,  LexType::TypeDecList,   LexType::TypeDecMore,
    LexType::TypeId,          LexType::TypeName,            LexType::BaseType,      LexType::StructureType,
    LexType::ArrayType,      LexType::Low,              LexType::Top,            LexType::RecType,
    LexType::FieldDecList,   LexType::FieldDecMore,     LexType::IdList,            LexType::IdMore,
    LexType::VarDec,          LexType::VarDeclaration,  LexType::VarDecList,        LexType::VarDecMore,
    LexType::VarIdList,   LexType::VarIdMore,       LexType::ProcDec,       LexType::ProcDeclaration,
    LexType::ProcDecMore,    LexType::ProcName,         LexType::ParamList,     LexType::ParamDecList,
    LexType::ParamMore,      LexType::Param,            LexType::FormList,      LexType::FidMore,
    LexType::ProcDecPart,    LexType::ProcBody,         LexType::ProgramBody,   LexType::StmList,
    LexType::StmMore,        LexType::Stm,              LexType::AssCall,       LexType::AssignmentRest,
    LexType::ConditionalStm, LexType::StmL,             LexType::LoopStm,       LexType::InputStm,
    LexType::InVar,          LexType::OutputStm,        LexType::ReturnStm,     LexType::CallStmRest,
    LexType::ActParamList,   LexType::ActParamMore,     LexType::RelExp,            LexType::OtherRelE,
    LexType::Exp,             LexType::OtherTerm,       LexType::Term,           LexType::OtherFactor,
    LexType::Factor,         LexType::Variable,         LexType::VariMore,      LexType::FieldVar,
    LexType::FieldVarMore,   LexType::CmpOp,            LexType::AddOp,          LexType::MultOp
};

