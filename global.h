#ifndef GLOBAL_H
#define GLOBAL_H
#include <QMap>
#include <QString>

enum class LexType
{
    /* 簿记单词符号 */
    ENDFILE,
    ERROR,

    /* 保留字 */
    PROGRAM,
    PROCEDURE,
    TYPE,
    VAR,
    IF,
    THEN,
    ELSE,
    FI,
    WHILE,
    DO,
    ENDWH,
    BEGIN,
    END,
    READ,
    WRITE,
    ARRAY,
    OF,
    RECORD,
    RETURN,

    /* 类型 */
    INTEGER_T,
    CHAR_T,

    /* 多字符单词符号 */
    ID,
    INTC_VAL,
    CHARC_VAL,

    /* 特殊符号 */
    ASSIGN,
    EQ,
    LT,
    PLUS,
    MINUS,
    TIMES,
    DIVIDE,
    LPAREN,
    RPAREN,
    DOT,
    COLON,
    SEMI,
    COMMA,
    LMIDPAREN,
    RMIDPAREN,
    UNDERANGE,

    /* 非终结符 */
    Program,
    ProgramHead,
    ProgramName,
    DeclarePart,
    TypeDec,
    TypeDeclaration,
    TypeDecList,
    TypeDecMore,
    TypeId,
    TypeName,
    BaseType,
    StructureType,
    ArrayType,
    Low,
    Top,
    RecType,
    FieldDecList,
    FieldDecMore,
    IdList,
    IdMore,
    VarDec,
    VarDeclaration,
    VarDecList,
    VarDecMore,
    VarIdList,
    VarIdMore,
    ProcDec,
    ProcDeclaration,
    ProcDecMore,
    ProcName,
    ParamList,
    ParamDecList,
    ParamMore,
    Param,
    FormList,
    FidMore,
    ProcDecPart,
    ProcBody,
    ProgramBody,
    StmList,
    StmMore,
    Stm,
    AssCall,
    AssignmentRest,
    ConditionalStm,
    StmL,
    LoopStm,
    InputStm,
    InVar,
    OutputStm,
    ReturnStm,
    CallStmRest,
    ActParamList,
    ActParamMore,
    RelExp,
    OtherRelE,
    Exp,
    OtherTerm,
    Term,
    OtherFactor,
    Factor,
    Variable,
    VariMore,
    FieldVar,
    FieldVarMore,
    CmpOp,
    AddOp,
    MultOp
};
enum class NodeKind
{
    /* 标志结点 */
    ProK, // 根标志结点
    PheadK, // 程序头标志结点
    TypeK, // 类型声明标志结点
    VarK, // 变量声明标志结点
    ProcDecK, // 函数声明标志结点
    StmLK, // 语句序列标志结点
    /* 具体结点 */
    DecK, // 声明结点
    StmtK, // 语句结点
    ExpK //表达式结点
};
enum class DecKind
{
    ArrayK, // 组类型
    CharK, // 字符类型
    IntegerK, // 整数类型
    RecordK, // 记录类型
    IdK // 类型标识符作为类型
};
enum class StmtKind
{
    IfK, // 判断语句类型
    WhileK, // 循环语句类型
    AssignK, // 赋值语句类型
    ReadK, // 读语句类型
    WriteK, // 写语句类型
    CallK, // 函数调用语句类型
    ReturnK // 返回语句类型
};
enum class ExpKind
{
    OpK, // 操作符类型
    ConstK, // 常整数类型
    IdK // 标识符类型
};
union Kind
{
    DecKind dec;
    StmtKind stmt;
    ExpKind exp;
};
enum class ParamType
{
    valparamType, // 表示过程的参数是值参
    varparamType // 表示过程的参数是变参
};
enum class VarKind
{
    IdV, // 变量是标识符变量
    ArrayMembV, // 变量是数组成员变量
    FieldMembV // 变量是域成员变量
};
enum class ExpType
{
    Void,
    Integer,
    Boolean
};

struct Symbtable;

namespace ConstantVar
{
extern QMap<LexType, QString> lexName;
extern QMap<QString, LexType> reservedWords;
extern QMap<char, LexType> opWords;
extern QMap<NodeKind, QString> nodekindName;
}

#endif // GLOBAL_H
