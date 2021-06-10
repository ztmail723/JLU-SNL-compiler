#include "parserll1.h"
int ParserLL1::nowLine = 0;
ParserLL1::ParserLL1()
{
    this->table =
    {
        { { LexType::Program, LexType::PROGRAM }, 1 },
        { { LexType::ProgramHead, LexType::PROGRAM }, 2 },
        { { LexType::ProgramName, LexType::ID }, 3 },
        { { LexType::DeclarePart, LexType::TYPE }, 4 },
        { { LexType::DeclarePart, LexType::VAR }, 4 },
        { { LexType::DeclarePart, LexType::PROCEDURE }, 4 },
        { { LexType::DeclarePart, LexType::BEGIN }, 4 },
        { { LexType::TypeDec, LexType::TYPE }, 6 },
        { { LexType::TypeDec, LexType::VAR }, 5 },
        { { LexType::TypeDec, LexType::PROCEDURE }, 5 },
        { { LexType::TypeDec, LexType::BEGIN }, 5 },
        { { LexType::TypeDeclaration, LexType::TYPE }, 7 },
        { { LexType::TypeDecList, LexType::ID }, 8 },
        { { LexType::TypeDecMore, LexType::VAR }, 9 },
        { { LexType::TypeDecMore, LexType::PROCEDURE }, 9 },
        { { LexType::TypeDecMore, LexType::BEGIN }, 9 },
        { { LexType::TypeDecMore, LexType::ID }, 10 },
        { { LexType::TypeId, LexType::ID }, 11 },
        { { LexType::TypeName, LexType::INTEGER_T }, 12 },
        { { LexType::TypeName, LexType::CHAR_T }, 12 },
        { { LexType::TypeName, LexType::ARRAY }, 13 },
        { { LexType::TypeName, LexType::RECORD }, 13 },
        { { LexType::TypeName, LexType::ID }, 14 },
        { { LexType::BaseType, LexType::INTEGER_T }, 15 },
        { { LexType::BaseType, LexType::CHAR_T }, 16 },
        { { LexType::StructureType, LexType::ARRAY }, 17 },
        { { LexType::StructureType, LexType::RECORD }, 18 },
        { { LexType::ArrayType, LexType::ARRAY }, 19 },
        { { LexType::Low, LexType::INTC_VAL }, 20 },
        { { LexType::Top, LexType::INTC_VAL }, 21 },
        { { LexType::RecType, LexType::RECORD }, 22 },
        { { LexType::FieldDecList, LexType::INTEGER_T }, 23 },
        { { LexType::FieldDecList, LexType::CHAR_T }, 23 },
        { { LexType::FieldDecList, LexType::ARRAY }, 24 },
        { { LexType::FieldDecMore, LexType::INTEGER_T }, 26 },
        { { LexType::FieldDecMore, LexType::CHAR_T }, 26 },
        { { LexType::FieldDecMore, LexType::ARRAY }, 26 },
        { { LexType::FieldDecMore, LexType::END }, 25 },
        { { LexType::IdList, LexType::ID }, 27 },
        { { LexType::IdMore, LexType::SEMI }, 28 },
        { { LexType::IdMore, LexType::COMMA }, 29 },
        { { LexType::VarDec, LexType::VAR }, 31 },
        { { LexType::VarDec, LexType::PROCEDURE }, 30 },
        { { LexType::VarDec, LexType::BEGIN }, 30 },
        { { LexType::VarDeclaration, LexType::VAR }, 32 },
        { { LexType::VarDecList, LexType::INTEGER_T }, 33 },
        { { LexType::VarDecList, LexType::CHAR_T }, 33 },
        { { LexType::VarDecList, LexType::ARRAY }, 33 },
        { { LexType::VarDecList, LexType::RECORD }, 33 },
        { { LexType::VarDecList, LexType::ID }, 33 },
        { { LexType::VarDecMore, LexType::INTEGER_T }, 35 },
        { { LexType::VarDecMore, LexType::CHAR_T }, 35 },
        { { LexType::VarDecMore, LexType::ARRAY }, 35 },
        { { LexType::VarDecMore, LexType::RECORD }, 35 },
        { { LexType::VarDecMore, LexType::PROCEDURE }, 34 },
        { { LexType::VarDecMore, LexType::BEGIN }, 34 },
        { { LexType::VarDecMore, LexType::ID }, 35 },
        { { LexType::VarIdList, LexType::ID }, 36 },
        { { LexType::VarIdMore, LexType::SEMI }, 37 },
        { { LexType::VarIdMore, LexType::COMMA }, 38 },
        { { LexType::ProcDec, LexType::PROCEDURE }, 40 },
        { { LexType::ProcDec, LexType::BEGIN }, 39 },
        { { LexType::ProcDeclaration, LexType::PROCEDURE }, 41 },
        { { LexType::ProcDecMore, LexType::PROCEDURE }, 41 },
        { { LexType::ProcDecMore, LexType::BEGIN }, 42 },
        { { LexType::ProcName, LexType::ID }, 44 },
        { { LexType::ParamList, LexType::INTEGER_T }, 46 },
        { { LexType::ParamList, LexType::CHAR_T }, 46 },
        { { LexType::ParamList, LexType::ARRAY }, 46 },
        { { LexType::ParamList, LexType::RECORD }, 46 },
        { { LexType::ParamList, LexType::VAR }, 46 },
        { { LexType::ParamList, LexType::ID }, 46 },
        { { LexType::ParamList, LexType::RMIDPAREN }, 45 },
        { { LexType::ParamDecList, LexType::INTEGER_T }, 47 },
        { { LexType::ParamDecList, LexType::CHAR_T }, 47 },
        { { LexType::ParamDecList, LexType::ARRAY }, 47 },
        { { LexType::ParamDecList, LexType::RECORD }, 47 },
        { { LexType::ParamDecList, LexType::VAR }, 47 },
        { { LexType::ParamDecList, LexType::ID }, 47 },
        { { LexType::ParamMore, LexType::SEMI }, 49 },
        { { LexType::ParamMore, LexType::RPAREN }, 48 },
        { { LexType::Param, LexType::INTEGER_T }, 50 },
        { { LexType::Param, LexType::CHAR_T }, 50 },
        { { LexType::Param, LexType::ARRAY }, 50 },
        { { LexType::Param, LexType::RECORD }, 50 },
        { { LexType::Param, LexType::END }, 51 },
        { { LexType::Param, LexType::ID }, 50 },
        { { LexType::Param, LexType::VAR }, 51 },
        { { LexType::FormList, LexType::ID }, 52 },
        { { LexType::FidMore, LexType::SEMI }, 53 },
        { { LexType::FidMore, LexType::COMMA }, 54 },
        { { LexType::FidMore, LexType::RPAREN }, 53 },
        { { LexType::ProcDecPart, LexType::TYPE }, 55 },
        { { LexType::ProcDecPart, LexType::VAR }, 55 },
        { { LexType::ProcDecPart, LexType::PROCEDURE }, 55 },
        { { LexType::ProcDecPart, LexType::BEGIN }, 55 },
        { { LexType::ProcBody, LexType::BEGIN }, 56 },
        { { LexType::ProgramBody, LexType::BEGIN }, 57 },
        { { LexType::StmList, LexType::IF }, 58 },
        { { LexType::StmList, LexType::WHILE }, 58 },
        { { LexType::StmList, LexType::READ }, 58 },
        { { LexType::StmList, LexType::WRITE }, 58 },
        { { LexType::StmList, LexType::RETURN }, 58 },
        { { LexType::StmList, LexType::ID }, 58 },
        { { LexType::StmMore, LexType::END }, 59 },
        { { LexType::StmMore, LexType::ELSE }, 59 },
        { { LexType::StmMore, LexType::FI }, 59 },
        { { LexType::StmMore, LexType::ENDWH }, 59 },
        { { LexType::StmMore, LexType::SEMI }, 60 },
        { { LexType::Stm, LexType::IF }, 61 },
        { { LexType::Stm, LexType::WHILE }, 62 },
        { { LexType::Stm, LexType::READ }, 63 },
        { { LexType::Stm, LexType::WRITE }, 64 },
        { { LexType::Stm, LexType::RETURN }, 65 },
        { { LexType::Stm, LexType::ID }, 66 },
        { { LexType::AssCall, LexType::ASSIGN }, 67 },
        { { LexType::AssCall, LexType::DOT }, 67 },
        { { LexType::AssCall, LexType::LMIDPAREN }, 67 },
        { { LexType::AssCall, LexType::LPAREN }, 68 },
        { { LexType::AssignmentRest, LexType::DOT }, 69 },
        { { LexType::AssignmentRest, LexType::LMIDPAREN }, 69 },
        { { LexType::AssignmentRest, LexType::ASSIGN }, 69 },
        { { LexType::ConditionalStm, LexType::IF }, 70 },
        { { LexType::LoopStm, LexType::WHILE }, 71 },
        { { LexType::InputStm, LexType::READ }, 72 },
        { { LexType::InVar, LexType::ID }, 73 },
        { { LexType::OutputStm, LexType::WRITE }, 74 },
        { { LexType::ReturnStm, LexType::RETURN }, 75 },
        { { LexType::CallStmRest, LexType::LPAREN }, 76 },
        { { LexType::ActParamList, LexType::INTC_VAL }, 78 },
        { { LexType::ActParamList, LexType::ID }, 78 },
        { { LexType::ActParamList, LexType::LPAREN }, 78 },
        { { LexType::ActParamList, LexType::RPAREN }, 77 },
        { { LexType::ActParamMore, LexType::COMMA }, 80 },
        { { LexType::ActParamMore, LexType::RPAREN }, 79 },
        { { LexType::RelExp, LexType::INTC_VAL }, 81 },
        { { LexType::RelExp, LexType::ID }, 81 },
        { { LexType::RelExp, LexType::LMIDPAREN }, 81 },
        { { LexType::OtherRelE, LexType::LT }, 82 },
        { { LexType::OtherRelE, LexType::EQ }, 82 },
        { { LexType::Exp, LexType::INTC_VAL }, 83 },
        { { LexType::OtherFactor, LexType::END }, 87 },
        { { LexType::OtherFactor, LexType::THEN }, 87 },
        { { LexType::OtherFactor, LexType::ELSE }, 87 },
        { { LexType::OtherFactor, LexType::FI }, 87 },
        { { LexType::OtherFactor, LexType::DO }, 87 },
        { { LexType::OtherFactor, LexType::ENDWH }, 87 },
        { { LexType::OtherFactor, LexType::SEMI }, 87 },
        { { LexType::OtherFactor, LexType::COMMA }, 87 },
        { { LexType::OtherFactor, LexType::RPAREN }, 87 },
        { { LexType::OtherFactor, LexType::RMIDPAREN }, 87 },
        { { LexType::OtherFactor, LexType::LT }, 87 },
        { { LexType::OtherFactor, LexType::EQ }, 87 },
        { { LexType::OtherFactor, LexType::PLUS }, 87 },
        { { LexType::OtherFactor, LexType::MINUS }, 87 },
        { { LexType::OtherFactor, LexType::TIMES }, 88 },
        { { LexType::OtherFactor, LexType::DIVIDE }, 88 },
        { { LexType::Term, LexType::INTC_VAL }, 86 },
        { { LexType::Factor, LexType::INTC_VAL }, 90 },
        { { LexType::OtherTerm, LexType::END }, 84 },
        { { LexType::Term, LexType::END }, 87 },
        { { LexType::VariMore, LexType::END }, 93 },
        { { LexType::FieldVarMore, LexType::END }, 97 },
        { { LexType::OtherTerm, LexType::THEN }, 84 },
        { { LexType::Term, LexType::THEN }, 87 },
        { { LexType::VariMore, LexType::THEN }, 93 },
        { { LexType::FieldVarMore, LexType::THEN }, 97 },
        { { LexType::OtherTerm, LexType::ELSE }, 84 },
        { { LexType::Term, LexType::ELSE }, 87 },
        { { LexType::VariMore, LexType::ELSE }, 93 },
        { { LexType::FieldVarMore, LexType::ELSE }, 97 },
        { { LexType::OtherTerm, LexType::FI }, 84 },
        { { LexType::Term, LexType::FI }, 87 },
        { { LexType::VariMore, LexType::FI }, 93 },
        { { LexType::FieldVarMore, LexType::FI }, 97 },
        { { LexType::OtherTerm, LexType::DO }, 84 },
        { { LexType::Term, LexType::DO }, 87 },
        { { LexType::VariMore, LexType::DO }, 93 },
        { { LexType::FieldVarMore, LexType::DO }, 97 },
        { { LexType::OtherTerm, LexType::ENDWH }, 84 },
        { { LexType::Term, LexType::ENDWH }, 87 },
        { { LexType::VariMore, LexType::ENDWH }, 93 },
        { { LexType::FieldVarMore, LexType::ENDWH }, 97 },
        { { LexType::Exp, LexType::ID }, 83 },
        { { LexType::Term, LexType::ID }, 86 },
        { { LexType::Factor, LexType::ID }, 91 },
        { { LexType::Variable, LexType::ID }, 92 },
        { { LexType::FieldVar, LexType::ID }, 96 },
        { { LexType::VariMore, LexType::DOT }, 95 },
        { { LexType::OtherTerm, LexType::SEMI }, 84 },
        { { LexType::Term, LexType::SEMI }, 87 },
        { { LexType::VariMore, LexType::SEMI }, 93 },
        { { LexType::FieldVarMore, LexType::SEMI }, 97 },
        { { LexType::OtherTerm, LexType::COMMA }, 84 },
        { { LexType::Term, LexType::COMMA }, 87 },
        { { LexType::VariMore, LexType::COMMA }, 93 },
        { { LexType::FieldVarMore, LexType::COMMA }, 97 },
        { { LexType::Exp, LexType::LPAREN }, 83 },
        { { LexType::Term, LexType::LPAREN }, 86 },
        { { LexType::Factor, LexType::LPAREN }, 89 },
        { { LexType::OtherTerm, LexType::RPAREN }, 84 },
        { { LexType::Term, LexType::RPAREN }, 87 },
        { { LexType::VariMore, LexType::RPAREN }, 93 },
        { { LexType::FieldVarMore, LexType::RPAREN }, 97 },
        { { LexType::VariMore, LexType::LMIDPAREN }, 94 },
        { { LexType::FieldVarMore, LexType::LMIDPAREN }, 98 },
        { { LexType::OtherTerm, LexType::RMIDPAREN }, 84 },
        { { LexType::Term, LexType::RMIDPAREN }, 87 },
        { { LexType::VariMore, LexType::RMIDPAREN }, 93 },
        { { LexType::FieldVarMore, LexType::RMIDPAREN }, 97 },
        { { LexType::OtherTerm, LexType::LT }, 84 },
        { { LexType::Term, LexType::LT }, 87 },
        { { LexType::VariMore, LexType::LT }, 93 },
        { { LexType::FieldVarMore, LexType::LT }, 97 },
        { { LexType::CmpOp, LexType::LT }, 99 },
        { { LexType::OtherTerm, LexType::EQ }, 84 },
        { { LexType::Term, LexType::EQ }, 87 },
        { { LexType::VariMore, LexType::EQ }, 93 },
        { { LexType::FieldVarMore, LexType::EQ }, 97 },
        { { LexType::CmpOp, LexType::EQ }, 100 },
        { { LexType::OtherTerm, LexType::PLUS }, 85 },
        { { LexType::Term, LexType::PLUS }, 87 },
        { { LexType::VariMore, LexType::PLUS }, 93 },
        { { LexType::FieldVarMore, LexType::PLUS }, 97 },
        { { LexType::AddOp, LexType::PLUS }, 101 },
        { { LexType::OtherTerm, LexType::MINUS }, 85 },
        { { LexType::Term, LexType::MINUS }, 87 },
        { { LexType::VariMore, LexType::MINUS }, 93 },
        { { LexType::FieldVarMore, LexType::MINUS }, 97 },
        { { LexType::AddOp, LexType::MINUS }, 102 },
        { { LexType::Term, LexType::TIMES }, 88 },
        { { LexType::VariMore, LexType::TIMES }, 93 },
        { { LexType::FieldVarMore, LexType::TIMES }, 97 },
        { { LexType::MultOp, LexType::TIMES }, 103 },
        { { LexType::Term, LexType::DIVIDE }, 88 },
        { { LexType::VariMore, LexType::DIVIDE }, 93 },
        { { LexType::FieldVarMore, LexType::DIVIDE }, 97 },
        { { LexType::MultOp, LexType::DIVIDE }, 104 },
        { { LexType::VariMore, LexType::ASSIGN }, 93 },
        { { LexType::FieldVarMore, LexType::ASSIGN }, 97 },
        { { LexType::CmpOp, LexType::LT }, 99 },
        { { LexType::CmpOp, LexType::EQ }, 100 },
        { { LexType::AddOp, LexType::PLUS }, 101 },
        { { LexType::AddOp, LexType::MINUS }, 102 },
        { { LexType::MultOp, LexType::TIMES }, 103 },
        { { LexType::MultOp, LexType::DIVIDE }, 104 },
    };
}
TreeNode* ParserLL1::newSpecNode(NodeKind kind)
{
    auto t = new TreeNode;
    int i;
    for (i = 0; i < 3; i++)
    {
        t->child[i] = nullptr;
    }
    t->sibling = nullptr;
    t->nodekind = kind;
    //t->lineno = lineno;
    t->lineno = ParserLL1::nowLine;
    t->idnum = 0;
    for (i = 0; i < 10; i++)
    {
        t->table[i] = nullptr;
    }
    return t;
}

TreeNode* ParserLL1::newStmtNode(StmtKind kind)
{
    auto t = ParserLL1::newSpecNode(NodeKind::StmtK);
    t->kind.stmt = kind;
    return t;
}

TreeNode* ParserLL1::newExpNode(ExpKind kind)
{
    auto t = ParserLL1::newSpecNode(NodeKind::ExpK);
    t->kind.exp = kind;
    return t;
}

SyntaxTree* ParserLL1::run(TokenList tokenList)
{
    int tokenListSize = tokenList.size();
    int head = 0;
    SyntaxTree* syntaxTree = new SyntaxTree();
    syntaxTree->setRoot(ParserLL1::newSpecNode(NodeKind::ProK));
    symbal_stack.push(LexType::Program);
    syntaxtree_stack.push(&syntaxTree->getRoot()->child[2]);
    syntaxtree_stack.push(&syntaxTree->getRoot()->child[1]);
    syntaxtree_stack.push(&syntaxTree->getRoot()->child[0]);

    return syntaxTree;
}

int ParserLL1::getPriosity(LexType op)
{
    int pri = 0;
    switch (op)
    {
    case LexType::END:
        pri = -1;
        break; //栈底标识，优先级最低
    case LexType::LPAREN:
        pri = 0;
    case LexType::LT:
    case LexType::EQ:
        pri = 1;
        break;
    case LexType::PLUS:
    case LexType::MINUS:
        pri = 2;
        break;
    case LexType::TIMES:
    case LexType::DIVIDE:
        pri = 3;
        break;
    default:
        pri = -1;
    }
    return pri;
}

void ParserLL1::process(int id)
{
    switch (id)
    {
    case 1:
    {
        symbal_stack.push(LexType::DOT);
        symbal_stack.push(LexType::ProgramBody);
        symbal_stack.push(LexType::DeclarePart);
        symbal_stack.push(LexType::ProgramHead);
        break;
    }
    case 2:
    {
        symbal_stack.push(LexType::ProgramName);
        symbal_stack.push(LexType::PROGRAM);
        current_treenode = ParserLL1::newSpecNode(NodeKind::PheadK);
        auto item = syntaxtree_stack.pop();
        (*item) = current_treenode;
        break;
    }
    case 3:
    {
        symbal_stack.push(LexType::ID);
        current_treenode->name[0] = head->getSem();
        ++current_treenode->idnum;
        break;
    }
    case 4:
    {
        symbal_stack.push(LexType::ProcDec);
        symbal_stack.push(LexType::VarDec);
        symbal_stack.push(LexType::TypeDec);
        break;
    }
    case 5:
    {
        break;
    }
    case 6:
    {
        symbal_stack.push(LexType::TypeDeclaration);
        break;
    }
    case 7:
    {
        symbal_stack.push(LexType::TypeDecList);
        symbal_stack.push(LexType::TYPE);

        auto t = syntaxtree_stack.pop();
        current_treenode = ParserLL1::newSpecNode(NodeKind::TypeK);

        (*t) = current_treenode;
        syntaxtree_stack.push(&(current_treenode->sibling));
        syntaxtree_stack.push(&(current_treenode->child[0]));

        break;
    }
    case 8:
    {

        symbal_stack.push(LexType::TypeDecMore);
        symbal_stack.push(LexType::SEMI);
        symbal_stack.push(LexType::TypeName);
        symbal_stack.push(LexType::EQ);
        symbal_stack.push(LexType::TypeId);

        auto t = syntaxtree_stack.pop();

        current_treenode = ParserLL1::newSpecNode(NodeKind::DecK);
        (*t) = current_treenode;

        syntaxtree_stack.push(&(current_treenode->sibling));
        break;
    }
    case 9:
    {
        syntaxtree_stack.pop();
        break;
    }
    case 10:
    {
        symbal_stack.push(LexType::TypeDecList);
        break;
    }
    case 11:
    {
        symbal_stack.push(LexType::ID);
        current_treenode->name[0] = head->getSem();
        current_treenode->idnum++;
        break;
    }
    case 12:
    {
        symbal_stack.push(LexType::BaseType);
        temp = &(current_treenode->kind.dec);
        break;
    }
    case 13:
    {
        symbal_stack.push(LexType::StructureType);
        break;
    }
    case 14:
    {
        symbal_stack.push(LexType::ID);
        current_treenode->kind.dec = DecKind::IdK;
        current_treenode->type_name = head->getSem();
        break;
    }
    case 15:
    {
        symbal_stack.push(LexType::INTEGER_T);
        (*temp) = DecKind::IntegerK;
        break;
    }
    case 16:
    {
        symbal_stack.push(LexType::CHAR_T);
        (*temp) = DecKind::CharK;
        break;
    }
    case 17:
    {
        symbal_stack.push(LexType::ArrayType);

        break;
    }
    case 18:
    {
        symbal_stack.push(LexType::RecType);
        break;
    }
    case 19:
    {
        symbal_stack.push(LexType::BaseType);
        symbal_stack.push(LexType::OF);
        symbal_stack.push(LexType::RMIDPAREN);
        symbal_stack.push(LexType::Top);
        symbal_stack.push(LexType::UNDERANGE);
        symbal_stack.push(LexType::Low);
        symbal_stack.push(LexType::LMIDPAREN);
        symbal_stack.push(LexType::ARRAY);

        current_treenode->kind.dec = DecKind::ArrayK;
        temp = &current_treenode->attr.ArrayAttr.childtype;
        break;
    }
    case 20:
    {
        symbal_stack.push(LexType::INTC_VAL);
        current_treenode->attr.ArrayAttr.low = head->getSem().toInt();
        break;
    }
    case 21:
    {
        symbal_stack.push(LexType::INTC_VAL);
        current_treenode->attr.ArrayAttr.up = head->getSem().toInt();
        break;
    }
    case 22:
    {
        symbal_stack.push(LexType::END);
        symbal_stack.push(LexType::FieldDecList);
        symbal_stack.push(LexType::RECORD);
        current_treenode->kind.dec = DecKind::RecordK;
        saveP = current_treenode;
        syntaxtree_stack.push(&(current_treenode->child[0]));
        break;
    }
    case 23:
    {
        symbal_stack.push(LexType::FieldDecMore);
        symbal_stack.push(LexType::SEMI);
        symbal_stack.push(LexType::IdList);
        symbal_stack.push(LexType::BaseType);
        auto t = syntaxtree_stack.pop();
        current_treenode = ParserLL1::newSpecNode(NodeKind::DecK);
        temp = &current_treenode->kind.dec;
        (*t) = current_treenode;
        syntaxtree_stack.push(&current_treenode->sibling);
        break;
    }
    case 24:
    {
        symbal_stack.push(LexType::FieldDecMore);
        symbal_stack.push(LexType::SEMI);
        symbal_stack.push(LexType::IdList);
        symbal_stack.push(LexType::ArrayType);

        TreeNode** t = syntaxtree_stack.pop();
        current_treenode = ParserLL1::newSpecNode(NodeKind::DecK); /*生成记录类型的下一个域，不添任何信息*/
        (*t) = current_treenode; /*若是第一个，则是record类型的子结点指向当前结点，否则，是上一个纪录域声明的兄弟结点*/
        syntaxtree_stack.push(&((*current_treenode).sibling));

        break;
    }
    case 25:
    {
        /*后面没有记录类型的下一个域了，恢复当前纪录类型节点的指针*/
        syntaxtree_stack.pop();
        current_treenode = saveP;
        break;
    }

    case 26:
    {
        symbal_stack.push(LexType::FieldDecList);
        break;
    }
    case 27:
    {
        symbal_stack.push(LexType::IdMore);
        symbal_stack.push(LexType::ID);

        /*纪录一个域中各个变量的语义信息*/
        current_treenode->name[current_treenode->idnum] = head->getSem();
        current_treenode->idnum++;
        break;
    }
    case 28:
    {
        break;
    }

    case 29:
    {
        symbal_stack.push(LexType::IdList);
        symbal_stack.push(LexType::COMMA);

        break;
    }
    case 30:
    {
        break;
    }

    case 31:
    {
        symbal_stack.push(LexType::VarDeclaration);

        break;
    }
    case 32:
    {
        symbal_stack.push(LexType::VarDecList);
        symbal_stack.push(LexType::VAR);

        current_treenode = ParserLL1::newSpecNode(NodeKind::VarK); /*生成一个标志变量声明的节点*/
        TreeNode** t = syntaxtree_stack.pop();
        (*t) = current_treenode;
        syntaxtree_stack.push(&((*current_treenode).sibling)); /*压入指向函数声明的指针*/
        syntaxtree_stack.push(&((*current_treenode).child[0])); /*压入指向第一个变量声明节点的指针*/

        break;
    }
    case 33:
    {
        symbal_stack.push(LexType::VarDecMore);
        symbal_stack.push(LexType::SEMI);
        symbal_stack.push(LexType::VarIdList);
        symbal_stack.push(LexType::TypeName);

        TreeNode** t = syntaxtree_stack.pop();
        current_treenode = ParserLL1::newSpecNode(NodeKind::DecK); /*建立一个新的声明节点，这里表示变量声明*/
        (*t) = current_treenode; /*若是第一个节点，则变量声明的头指针指向它，否则它是前一个变量声明的后继*/
        syntaxtree_stack.push(&((*current_treenode).sibling));

        break;
    }
    case 34:
    {
        syntaxtree_stack.pop();
        break;
    }

    case 35:
    {
        symbal_stack.push(LexType::VarDecList);
        break;
    }
    case 36:
    {
        symbal_stack.push(LexType::VarIdMore);
        symbal_stack.push(LexType::ID);

        current_treenode->name[current_treenode->idnum] = head->getSem();
        current_treenode->idnum++;
        break;
    }
    case 37:
    {
        break;
    }

    case 38:
    {
        symbal_stack.push(LexType::VarIdList);
        symbal_stack.push(LexType::COMMA);

        break;
    }
    case 39:
    {
        break;
    }

    case 40:
    {
        symbal_stack.push(LexType::ProcDeclaration);

        break;
    }
    case 41:
    {
        symbal_stack.push(LexType::ProcDecMore);
        symbal_stack.push(LexType::ProcBody);
        symbal_stack.push(LexType::ProcDecPart);
        symbal_stack.push(LexType::SEMI);
        symbal_stack.push(LexType::RPAREN);
        symbal_stack.push(LexType::ParamList);
        symbal_stack.push(LexType::LPAREN);
        symbal_stack.push(LexType::ProcName);
        symbal_stack.push(LexType::PROCEDURE);

        current_treenode = ParserLL1::newSpecNode(NodeKind::ProcDecK);
        TreeNode** t = syntaxtree_stack.pop();
        (*t) = current_treenode;

        syntaxtree_stack.push(&(current_treenode->sibling));
        syntaxtree_stack.push(&(current_treenode->child[2])); /*指向语句序列*/
        syntaxtree_stack.push(&(current_treenode->child[1])); /*指向函数的声明部分*/
        syntaxtree_stack.push(&(current_treenode->child[0])); /*指向参数声明部分*/
        break;
    }

    case 42:
    {
        /*弹出过程节点的兄弟节点指针*/
        //syntaxtree_stack.pop();  /*为了统一处理，不能现在弹出*/
        break;
    }

    case 43:
    {
        symbal_stack.push(LexType::ProcDeclaration);
        break;
    }

    case 44:
    {
        symbal_stack.push(LexType::ID);

        current_treenode->name[0] = head->getSem();
        current_treenode->idnum++;
        break;
    }

    case 45:
    {
        /*形参部分为空，弹出指向形参的指针*/
        syntaxtree_stack.pop();
        break;
    }

    case 46:
    {
        symbal_stack.push(LexType::ParamDecList);
        break;
    }
    case 47:
    {
        symbal_stack.push(LexType::ParamMore);
        symbal_stack.push(LexType::Param);
        break;
    }
    case 48:
    {
        syntaxtree_stack.pop();
        break;
    }

    case 49:
    {
        symbal_stack.push(LexType::ParamDecList);
        symbal_stack.push(LexType::SEMI);
        break;
    }
    case 50:
    {
        symbal_stack.push(LexType::FormList);
        symbal_stack.push(LexType::TypeName);

        TreeNode** t = syntaxtree_stack.pop();
        current_treenode = ParserLL1::newSpecNode(NodeKind::DecK);
        /*函数的参数类型是值类型*/
        current_treenode->attr.ProcAttr.paramt = ParamType::valparamType;
        (*t) = current_treenode;
        syntaxtree_stack.push(&(current_treenode->sibling));

        break;
    }
    case 51:
    {
        symbal_stack.push(LexType::FormList);
        symbal_stack.push(LexType::TypeName);
        symbal_stack.push(LexType::VAR);

        TreeNode** t = syntaxtree_stack.pop();
        current_treenode = ParserLL1::newSpecNode(NodeKind::DecK);
        /*函数的参数类型是变量类型*/
        current_treenode->attr.ProcAttr.paramt = ParamType::varparamType;
        (*t) = current_treenode;
        syntaxtree_stack.push(&(current_treenode->sibling));

        break;
    }
    case 52:
    {
        symbal_stack.push(LexType::FidMore);
        symbal_stack.push(LexType::ID);

        current_treenode->name[current_treenode->idnum] = head->getSem();
        current_treenode->idnum++;

        break;
    }
    case 53:
    {
        break;
    }

    case 54:
    {
        symbal_stack.push(LexType::FormList);
        symbal_stack.push(LexType::COMMA);
        break;
    }

    case 55:
    {
        symbal_stack.push(LexType::DeclarePart);
        break;
    }
    case 56:
    {
        symbal_stack.push(LexType::ProgramBody);
        break;
    }

    case 57:
    {
        symbal_stack.push(LexType::END);
        symbal_stack.push(LexType::StmList);
        symbal_stack.push(LexType::BEGIN);

        /*注意，若没有声明部分，则弹出的是程序或过程根节点中指向
          声明部分的指针child[1];若有声明部分，则弹出的是语句序列前
          的最后一个声明标识节点的兄弟指针；不管是哪种情况，都正好
          需要弹出语法树栈中的一个指针*/
        syntaxtree_stack.pop();

        /*建立语句序列标识节点*/
        TreeNode** t = syntaxtree_stack.pop();
        current_treenode = ParserLL1::newSpecNode(NodeKind::StmLK);
        (*t) = current_treenode;
        syntaxtree_stack.push(&(current_treenode->child[0]));
        break;
    }
    case 58:
    {
        symbal_stack.push(LexType::StmMore);
        symbal_stack.push(LexType::Stm);
        break;
    }
    case 59:
    {
        syntaxtree_stack.pop();
        break;
    }

    case 60:
    {
        symbal_stack.push(LexType::StmList);
        symbal_stack.push(LexType::SEMI);
        break;
    }
    case 61:
    {
        symbal_stack.push(LexType::ConditionalStm);

        current_treenode = ParserLL1::newStmtNode(StmtKind::IfK);
        //current_treenode->kind.stmt=;

        TreeNode** t = syntaxtree_stack.pop();
        (*t) = current_treenode;
        syntaxtree_stack.push(&current_treenode->sibling);

        break;
    }
    case 62:
    {
        symbal_stack.push(LexType::LoopStm);

        current_treenode = ParserLL1::newStmtNode(StmtKind::WhileK);
        //current_treenode->kind.stmt=;

        TreeNode** t = syntaxtree_stack.pop();
        (*t) = current_treenode;
        syntaxtree_stack.push(&current_treenode->sibling);

        break;
    }

    case 63:
    {
        symbal_stack.push(LexType::InputStm);

        TreeNode** t = syntaxtree_stack.pop();
        current_treenode = ParserLL1::newStmtNode(StmtKind::ReadK);
        //current_treenode->kind.stmt=;
        (*t) = current_treenode;
        syntaxtree_stack.push(&current_treenode->sibling);

        break;
    }
    case 64:
    {
        symbal_stack.push(LexType::OutputStm);

        TreeNode** t = syntaxtree_stack.pop();
        current_treenode = ParserLL1::newStmtNode(StmtKind::WriteK);
        //current_treenode->kind.stmt=;
        (*t) = current_treenode;
        syntaxtree_stack.push(&current_treenode->sibling);

        break;
    }
    case 65:
    {
        symbal_stack.push(LexType::ReturnStm);

        TreeNode** t = syntaxtree_stack.pop();
        current_treenode = ParserLL1::newStmtNode(StmtKind::ReturnK);
        //current_treenode->kind.stmt=;
        (*t) = current_treenode;
        syntaxtree_stack.push(&current_treenode->sibling);

        break;
    }

    case 66:
    {
        symbal_stack.push(LexType::AssCall);
        symbal_stack.push(LexType::ID);

        current_treenode = ParserLL1::newStmtNode(StmtKind::AssignK);

        /*赋值语句左部变量节点*/
        TreeNode* t = ParserLL1::newExpNode(ExpKind::VariK);
        t->name[0] = head->getSem();
        t->idnum++;

        /*赋值语句的child[0]指向左部的变量节点*/
        current_treenode->child[0] = t;

        TreeNode** t1 = syntaxtree_stack.pop();
        (*t1) = current_treenode;
        syntaxtree_stack.push(&current_treenode->sibling);

        break;
    }
    case 67:
    {
        symbal_stack.push(LexType::AssignmentRest);

        current_treenode->kind.stmt = StmtKind::AssignK;
        break;
    }
    case 68:
    {
        symbal_stack.push(LexType::CallStmRest);
        /*过程调用语句左部是标识符变量，表示过程名*/
        current_treenode->child[0]->attr.ExpAttr.varkind = VarKind::IdV;

        current_treenode->kind.stmt = StmtKind::CallK;
        break;
    }
    case 69:
    {
        symbal_stack.push(LexType::Exp);
        symbal_stack.push(LexType::ASSIGN);
        symbal_stack.push(LexType::VariMore);
        /*压入指向赋值右部的指针*/
        syntaxtree_stack.push(&(current_treenode->child[1]));
        /*当前指针指向赋值左部*/
        current_treenode = current_treenode->child[0];

        TreeNode* t = ParserLL1::newExpNode(ExpKind::OpK);
        t->attr.ExpAttr.op = LexType::END;
        op_stack.push(t); //操作符栈的栈底存入一个特殊的操作符作为标志
        break;
    }
    case 70:
    {
        symbal_stack.push(LexType::FI);
        symbal_stack.push(LexType::StmList);
        symbal_stack.push(LexType::ELSE);
        symbal_stack.push(LexType::StmList);
        symbal_stack.push(LexType::THEN);
        symbal_stack.push(LexType::RelExp);
        symbal_stack.push(LexType::IF);

        syntaxtree_stack.push(&(current_treenode->child[2]));
        syntaxtree_stack.push(&(current_treenode->child[1]));
        syntaxtree_stack.push(&(current_treenode->child[0]));

        break;
    }

    case 71:
    {
        symbal_stack.push(LexType::ENDWH);
        symbal_stack.push(LexType::StmList);
        symbal_stack.push(LexType::DO);
        symbal_stack.push(LexType::RelExp);
        symbal_stack.push(LexType::WHILE);

        syntaxtree_stack.push(&(current_treenode->child[1]));
        syntaxtree_stack.push(&(current_treenode->child[0]));

        break;
    }

    case 72:
    {
        symbal_stack.push(LexType::RPAREN);
        symbal_stack.push(LexType::InVar);
        symbal_stack.push(LexType::LPAREN);
        symbal_stack.push(LexType::READ);
        break;
    }
    case 73:
    {
        symbal_stack.push(LexType::ID);

        current_treenode->name[0] = head->getSem();
        current_treenode->idnum++;
        break;
    }
    case 74:
    {
        symbal_stack.push(LexType::RPAREN);
        symbal_stack.push(LexType::Exp);
        symbal_stack.push(LexType::LPAREN);
        symbal_stack.push(LexType::WRITE);

        syntaxtree_stack.push(&(current_treenode->child[0]));

        TreeNode* t = ParserLL1::newExpNode(ExpKind::OpK);
        t->attr.ExpAttr.op = LexType::END;
        op_stack.push(t); //操作符栈的栈底存入一个特殊的操作符作为标志
        break;
    }
    case 75:
    {
        symbal_stack.push(LexType::RETURN);
        break;
    }

    case 76:
    {
        symbal_stack.push(LexType::RPAREN);
        symbal_stack.push(LexType::ActParamList);
        symbal_stack.push(LexType::LPAREN);

        syntaxtree_stack.push(&(current_treenode->child[1]));
        break;
    }
    case 77:
    {
        syntaxtree_stack.pop();
        break;
    }
    case 78:
    {
        symbal_stack.push(LexType::ActParamMore);
        symbal_stack.push(LexType::Exp);

        TreeNode* t = ParserLL1::newExpNode(ExpKind::OpK);
        t->attr.ExpAttr.op = LexType::END;
        op_stack.push(t); //操作符栈的栈底存入一个特殊的操作符作为标志
        break;
    }

    case 79:
    {
        break;
    }
    case 80:
    {
        symbal_stack.push(LexType::ActParamList);
        symbal_stack.push(LexType::COMMA);

        syntaxtree_stack.push(&(current_treenode->sibling));
        break;
    }

    /*********************表达式部分************************/

    case 81:
    {
        symbal_stack.push(LexType::OtherRelE);
        symbal_stack.push(LexType::Exp);

        TreeNode* t = ParserLL1::newExpNode(ExpKind::OpK);
        t->attr.ExpAttr.op = LexType::END;
        op_stack.push(t); //操作符栈的栈底存入一个特殊的操作符作为标志

        getExpResult = false;
        break;
    }

    case 82:
    {
        symbal_stack.push(LexType::Exp);
        symbal_stack.push(LexType::CmpOp);

        TreeNode* current_treenode = ParserLL1::newExpNode(ExpKind::OpK);
        current_treenode->attr.ExpAttr.op = head->getLexType();

        LexType sTop = op_stack.top()->attr.ExpAttr.op;
        while (this->getPriosity(sTop) >= this->getPriosity(head->getLexType()))
            /*如果操作符栈顶运算符的优先级高于或等于当前读到的操作符*/
        {
            TreeNode* t = op_stack.pop();
            TreeNode* Rnum = num_stack.pop();
            TreeNode* Lnum = num_stack.pop();
            t->child[1] = Rnum;
            t->child[0] = Lnum;
            num_stack.push(t);

            sTop = op_stack.top()->attr.ExpAttr.op;
        }

        op_stack.push(current_treenode);
        /*处理完关系操作符右部的表达式时，要弹语法树栈，故
          设置getExpResult为真*/
        getExpResult = true;
        break;
    }

    case 83:
    {
        symbal_stack.push(LexType::OtherTerm);
        symbal_stack.push(LexType::Term);
        break;
    }

    case 84:
    {
        if ((head->getLexType() == LexType::RPAREN) && (expflag != 0))
            //说明当前右括号是表达式中的一部分
        {
            while (op_stack.top()->attr.ExpAttr.op != LexType::LPAREN)
            {
                TreeNode* t = op_stack.pop();
                TreeNode* Rnum = num_stack.pop();
                TreeNode* Lnum = num_stack.pop();

                t->child[1] = Rnum;
                t->child[0] = Lnum;
                num_stack.push(t);
            }
            op_stack.pop(); //弹出左括号
            expflag--;
        }
        else
        {
            if ((getExpResult) || (getExpResult2))
            {
                while (op_stack.top()->attr.ExpAttr.op != LexType::END)
                {
                    TreeNode* t = op_stack.pop();
                    TreeNode* Rnum = num_stack.pop();
                    TreeNode* Lnum = num_stack.pop();

                    t->child[1] = Rnum;
                    t->child[0] = Lnum;
                    num_stack.push(t);
                }
                op_stack.pop(); //弹出栈底标志
                current_treenode = num_stack.pop();

                TreeNode** t = syntaxtree_stack.pop();
                (*t) = current_treenode;

                /*处理完数组变量，标志恢复初始值假，
                  遇到下一个数组下标表达式时，再将其设置为真值*/
                if (getExpResult2 == true)
                    getExpResult2 = false;
            }
        }
        break;
    }

    case 85:
    {
        symbal_stack.push(LexType::Exp);
        symbal_stack.push(LexType::AddOp);

        TreeNode* current_treenode = ParserLL1::newExpNode(ExpKind::OpK);
        current_treenode->attr.ExpAttr.op = head->getLexType();
        LexType sTop = op_stack.top()->attr.ExpAttr.op;
        while (this->getPriosity(sTop) >= this->getPriosity(head->getLexType()))
        {
            TreeNode* t = op_stack.pop();
            TreeNode* Rnum = num_stack.pop();
            TreeNode* Lnum = num_stack.pop();
            t->child[1] = Rnum;
            t->child[0] = Lnum;
            num_stack.push(t);
            sTop = op_stack.top()->attr.ExpAttr.op;
        }
        op_stack.push(current_treenode);
        break;
    }

    case 86:
    {
        symbal_stack.push(LexType::OtherFactor);
        symbal_stack.push(LexType::Factor);
        break;
    }
    case 87:
    {
        break;
    }
    case 88:
    {
        symbal_stack.push(LexType::Term);
        symbal_stack.push(LexType::MultOp);

        TreeNode* current_treenode = ParserLL1::newExpNode(ExpKind::OpK);
        current_treenode->attr.ExpAttr.op = head->getLexType();

        LexType sTop = op_stack.top()->attr.ExpAttr.op;
        while (this->getPriosity(sTop) >= this->getPriosity(head->getLexType()))
            /*如果操作符栈顶运算符的优先级高于或等于当前读到的操作符*/
        {
            TreeNode* t = op_stack.pop();
            TreeNode* Rnum = num_stack.pop();
            TreeNode* Lnum = num_stack.pop();
            t->child[1] = Rnum;
            t->child[0] = Lnum;
            num_stack.push(t);

            sTop = op_stack.top()->attr.ExpAttr.op;
        }
        op_stack.push(current_treenode);
        break;
    }

    case 89:
    {
        symbal_stack.push(LexType::RPAREN);
        symbal_stack.push(LexType::Exp);
        symbal_stack.push(LexType::LPAREN);

        TreeNode* t = ParserLL1::newExpNode(ExpKind::OpK);
        t->attr.ExpAttr.op = head->getLexType(); /*把左括号也压入栈中*/
        op_stack.push(t);
        expflag++;
        break;
    }

    case 90:
    {
        symbal_stack.push(LexType::INTC_VAL);

        TreeNode* t = ParserLL1::newExpNode(ExpKind::ConstK);
        t->attr.ExpAttr.val = head->getSem().toInt();
        /*常数节点入操作数栈*/
        num_stack.push(t);

        break;
    }

    case 91:
    {
        symbal_stack.push(LexType::Variable);
        break;
    }

    case 92:
    {
        symbal_stack.push(LexType::VariMore);
        symbal_stack.push(LexType::ID);

        current_treenode = ParserLL1::newExpNode(ExpKind::VariK);
        current_treenode->name[0] = head->getSem();
        current_treenode->idnum++;
        /*变量节点入操作数栈*/
        num_stack.push(current_treenode);

        break;
    }

    case 93:
    {
        /*标识符变量*/
        current_treenode->attr.ExpAttr.varkind = VarKind::IdV;
        break;
    }

    case 94:
    {
        symbal_stack.push(LexType::RMIDPAREN);
        symbal_stack.push(LexType::Exp);
        symbal_stack.push(LexType::LMIDPAREN);
        /*数组成员变量*/
        current_treenode->attr.ExpAttr.varkind = VarKind::ArrayMembV;
        syntaxtree_stack.push(&current_treenode->child[0]);

        /*要进入表达式处理，初始化操作符栈*/
        //操作符栈的栈底存入一个特殊的操作符作为标志
        TreeNode* t = ParserLL1::newExpNode(ExpKind::OpK);
        t->attr.ExpAttr.op = LexType::END;
        op_stack.push(t);

        /*要进入数组下标表达式处理，在函数process84处理中，要
          操作语法树栈，故将标志getExpResult2设置为真值*/
        getExpResult2 = true;

        break;
    }

    case 95:
    {
        symbal_stack.push(LexType::FieldVar);
        symbal_stack.push(LexType::DOT);
        /*域成员变量*/
        current_treenode->attr.ExpAttr.varkind = VarKind::FieldMembV;
        syntaxtree_stack.push(&current_treenode->child[0]);
        break;
    }

    case 96:
    {
        symbal_stack.push(LexType::FieldVarMore);
        symbal_stack.push(LexType::ID);

        /*纪录域的成员*/
        current_treenode = ParserLL1::newExpNode(ExpKind::VariK);
        current_treenode->name[0] = head->getSem();
        current_treenode->idnum++;

        TreeNode** t = syntaxtree_stack.pop();
        (*t) = current_treenode;

        break;
    }

    case 97:
    {
        /*域成员是标识符变量*/
        current_treenode->attr.ExpAttr.varkind = VarKind::IdV;
        break;
    }

    case 98:
    {
        symbal_stack.push(LexType::RMIDPAREN);
        symbal_stack.push(LexType::Exp);
        symbal_stack.push(LexType::LMIDPAREN);
        /*域成员是数组变量*/
        current_treenode->attr.ExpAttr.varkind = VarKind::ArrayMembV;
        /*指向数组成员表达式*/
        syntaxtree_stack.push(&current_treenode->child[0]);

        //操作符栈的栈底存入一个特殊的操作符作为标志
        TreeNode* t = ParserLL1::newExpNode(ExpKind::OpK);
        t->attr.ExpAttr.op = LexType::END;
        op_stack.push(t);

        /*要进入数组下标表达式处理，在函数process84处理中，要
          操作语法树栈，故将标志getExpResult2设置为真值*/
        getExpResult2 = true;
        break;
    }
    case 99:
    {
        symbal_stack.push(LexType::LT);
        break;
    }

    case 100:
    {
        symbal_stack.push(LexType::EQ);
        break;
    }

    case 101:
    {
        symbal_stack.push(LexType::PLUS);
        break;
    }

    case 102:
    {
        symbal_stack.push(LexType::MINUS);
        break;
    }

    case 103:
    {
        symbal_stack.push(LexType::TIMES);
        break;
    }

    case 104:
    {
        symbal_stack.push(LexType::DIVIDE);
        break;
    }
    }
}
