#include "parserrecursivedescent.h"
#include <QMessageBox>

ParserRecursiveDescent::ParserRecursiveDescent()
{

}

SyntaxTree* ParserRecursiveDescent::run(TokenList tokenList)
{
    this->tokenList = tokenList;
    cur = 0;

    SyntaxTree* syntaxTree = new SyntaxTree();
    syntaxTree->setRoot(program());

    return syntaxTree;
}

bool ParserRecursiveDescent::match(LexType lexType)
{
    Token token = tokenList[cur];

    if (tokenList[cur].getLexType() == lexType) {
        cur ++;
        return true;
    }
    return false;
}

TreeNode* ParserRecursiveDescent::program()
{
    TreeNode* t = programHead();
    TreeNode* q = declarePart();
    TreeNode* s = programBody();

    TreeNode* root = new TreeNode(NodeKind::ProK, 0);

    if (t != nullptr)
        root->child[0] = t;
    else
        syntaxError("缺少程序头！");

    if (q != nullptr)
        root->child[1] = q;

    if (s != nullptr)
        root->child[2] = s;
    else
        syntaxError("缺少程序体！");

    if (!match(LexType::DOT))
        syntaxError("缺少程序结束符\".\"！");

    return root;
}

TreeNode* ParserRecursiveDescent::programHead()
{
    TreeNode* t = new TreeNode(NodeKind::PheadK, tokenList[cur].getLineShow());

    if (!match(LexType::PROGRAM))
        syntaxError("缺少程序开始标志\"PROGRAM\"！");

    programName(t);

    return t;
}

void ParserRecursiveDescent::programName(TreeNode* t)
{
    if (!match(LexType::ID))
        syntaxError("程序名字有误或缺失！");
    else {
        t->name[t->idnum] = tokenList[cur-1].getSem();
        t->idnum ++;
    }
}

TreeNode* ParserRecursiveDescent::declarePart()
{
    TreeNode* typeP = new TreeNode(NodeKind::TypeK, tokenList[cur].getLineShow());

    TreeNode* tp1 = typeDecpart();
    if (tp1 != nullptr)
        typeP->child[0] = tp1;
    else {
        delete typeP;
        typeP = nullptr;
    }

    TreeNode* varP = new TreeNode(NodeKind::VarK, tokenList[cur].getLineShow());

    TreeNode* tp2 = varDecpart();
    if (tp2 != nullptr)
        varP->child[0] = tp2;
    else {
        delete varP;
        varP = nullptr;
    }

    TreeNode* procP = procDecpart();

    if (varP == nullptr)
        varP = procP;

    if (typeP == nullptr)
        typeP = varP;

    if (typeP != varP)
        typeP->sibling = varP;

    if (varP != procP)
        varP->sibling = procP;

    return typeP;
}

TreeNode* ParserRecursiveDescent::typeDecpart()
{
    TreeNode* t = nullptr;
    switch (tokenList[cur].getLexType()) {
        case LexType::TYPE :
            t = typeDec();
            break;
        case LexType::VAR : break;
        case LexType::PROCEDURE : break;
        case LexType::BEGIN : break;
        default :
            syntaxError("出现预期外的符号：\"" + tokenList[cur].getSem() + "\"！");
            break;
    }
    return t;
}

TreeNode* ParserRecursiveDescent::typeDec()
{
    match(LexType::TYPE);
    TreeNode* t = typeDecList();
    if (t == nullptr)
        syntaxError("缺少类型定义内容声明！");
    return t;
}

TreeNode* ParserRecursiveDescent::typeDecList()
{
    TreeNode* t = new TreeNode(NodeKind::DecK, tokenList[cur].getLineShow());

    typeID(t);

    if(!match(LexType::EQ))
        syntaxError("类型声明缺少\"=\"");

    typeDef(t);

    if (!match(LexType::SEMI))
        syntaxError("缺少\";\"");

    t->sibling = typeDecMore();

    return t;
}

TreeNode* ParserRecursiveDescent::typeDecMore()
{
    TreeNode* p = nullptr;
    switch (tokenList[cur].getLexType()) {
        case LexType::VAR : break;
        case LexType::PROCEDURE : break;
        case LexType::BEGIN : break;
        case LexType::ID :
            p = typeDecList();
            break;
        default :
            syntaxError("出现预期外的符号：\"" + tokenList[cur].getSem() + "\"！");
            break;
    }
    return p;
}

void ParserRecursiveDescent::typeID(TreeNode* t)
{
    if (!match(LexType::ID))
        syntaxError("类型声明缺少标识符！");
    else {
        t->name[t->idnum] = tokenList[cur-1].getSem();
        t->idnum ++;
    }
}

void ParserRecursiveDescent::typeDef(TreeNode* t)
{
    switch(tokenList[cur].getLexType()) {
        case LexType::INTEGER_T :
            baseType(t);
            break;
        case LexType::CHAR_T :
            baseType(t);
            break;
        case LexType::ARRAY :
            structureType(t);
            break;
        case LexType::RECORD :
            structureType(t);
            break;
        case LexType::ID :
            match(LexType::ID);
            t->kind.dec = DecKind::IdK;
            t->type_name = tokenList[cur-1].getSem();
            break;
        default :
            syntaxError("出现未知类型：\"" + tokenList[cur].getSem() + "\"！");
            break;
    }
}

void ParserRecursiveDescent::baseType(TreeNode* t)
{
    switch (tokenList[cur].getLexType()) {
        case LexType::INTEGER_T :
            match(LexType::INTEGER_T);
            t->kind.dec = DecKind::IntegerK;
            break;
        case LexType::CHAR_T :
            match(LexType::CHAR_T);
            t->kind.dec = DecKind::CharK;
            break;
        default :
            syntaxError("出现未知类型：\"" + tokenList[cur].getSem() + "\"！");
            break;
    }
}

void ParserRecursiveDescent::structureType(TreeNode* t)
{
    switch (tokenList[cur].getLexType()) {
        case LexType::ARRAY :
            arrayType(t);
            break;
        case LexType::RECORD :
            recType(t);
            break;
        default :
            syntaxError("出现未知类型：\"" + tokenList[cur].getSem() + "\"！");
            break;
    }
}

void ParserRecursiveDescent::arrayType(TreeNode* t)
{
    if (!match(LexType::ARRAY))
        syntaxError("缺少数组声明：\"array\"！");

    if (!match(LexType::LMIDPAREN))
        syntaxError("缺少符号：\"[\"！");

    low(t);

    if (!match(LexType::UNDERANGE))
        syntaxError("缺少符号：\"..\"！");

    top(t);

    if (!match(LexType::RMIDPAREN))
        syntaxError("缺少符号：\"]\"！");

    if (!match(LexType::OF))
        syntaxError("缺少数组类型声明前置符：\"of\"！");

    baseType(t);

    t->attr.ArrayAttr.childtype = t->kind.dec;
    t->kind.dec = DecKind::ArrayK;
}

void ParserRecursiveDescent::low(TreeNode* t)
{
    if (!match(LexType::INTC_VAL))
        syntaxError("缺少数组下界！");

    t->attr.ArrayAttr.low = tokenList[cur-1].getSem().toInt();
}

void ParserRecursiveDescent::top(TreeNode* t)
{
    if (!match(LexType::INTC_VAL))
        syntaxError("缺少数组上界！");

    t->attr.ArrayAttr.up = tokenList[cur-1].getSem().toInt();
}

void ParserRecursiveDescent::recType(TreeNode* t)
{
    if (!match(LexType::RECORD))
        syntaxError("缺少记录声明：\"record\"！");

    TreeNode* p = fieldDecList();

    if (p != nullptr)
        t->child[0] = p;
    else
        syntaxError("缺少记录体！");

    if (!match(LexType::END))
        syntaxError("缺少记录结束声明：\"end\"！");

    t->kind.dec = DecKind::RecordK;
}

TreeNode* ParserRecursiveDescent::fieldDecList()
{
    TreeNode* t = new TreeNode(NodeKind::DecK, tokenList[cur].getLineShow());

    TreeNode* p = nullptr;
    switch (tokenList[cur].getLexType()) {
        case LexType::INTEGER_T :
            baseType(t);
            idList(t);
            if (!match(LexType::SEMI))
                syntaxError("缺少符号：\";\"！");
            p = fieldDecMore();
            break;
        case LexType::CHAR_T :
            baseType(t);
            idList(t);
            if (!match(LexType::SEMI))
                syntaxError("缺少符号：\";\"！");
            p = fieldDecMore();
            break;
        case LexType::ARRAY :
            arrayType(t);
            idList(t);
            if (!match(LexType::SEMI))
                syntaxError("缺少符号：\";\"！");
            p = fieldDecMore();
            break;
        default :
            syntaxError("记录体出现预期外变量类型：\"" + tokenList[cur].getSem() + "\"！");
            break;
    }
    t->sibling = p;

    return t;
}

TreeNode* ParserRecursiveDescent::fieldDecMore()
{
    TreeNode* p = nullptr;
    switch (tokenList[cur].getLexType()) {
        case LexType::END : break;
        case LexType::INTEGER_T :
            p = fieldDecList();
            break;
        case LexType::CHAR_T :
            p = fieldDecList();
            break;
        case LexType::ARRAY :
            p = fieldDecList();
            break;
        default :
            syntaxError("记录体出现预期外变量类型：\"" + tokenList[cur].getSem() + "\"！");
            break;
    }
    return p;
}

void ParserRecursiveDescent::idList(TreeNode* t)
{
    if (!match(LexType::ID))
        syntaxError("缺少标识符！");

    t->name[t->idnum] = tokenList[cur-1].getSem();
    t->idnum ++;

    idMore(t);
}

void ParserRecursiveDescent::idMore(TreeNode* t)
{
    switch (tokenList[cur].getLexType()) {
        case LexType::SEMI : break;
        case LexType::COMMA :
            idList(t);
            break;
        default :
            syntaxError("出现预期外的符号：\"" + tokenList[cur].getSem() + "\"！");
            break;
    }
}

TreeNode* ParserRecursiveDescent::varDecpart()
{
    TreeNode* t = nullptr;
    switch (tokenList[cur].getLexType()) {
        case LexType::PROCEDURE : break;
        case LexType::BEGIN : break;
        case LexType::VAR :
            t = varDec();
            break;
        default :
            syntaxError("出现预期外的符号：\"" + tokenList[cur].getSem() + "\"！");
            break;
    }
    return t;
}

TreeNode* ParserRecursiveDescent::varDec()
{
    if (!match(LexType::VAR))
        syntaxError("缺少变量声明：\"var\"");

    TreeNode* t = varDecList();
    if (t == nullptr)
        syntaxError("缺少变量声明内容！");

    return t;
}

TreeNode* ParserRecursiveDescent::varDecList()
{
    TreeNode* t = new TreeNode(NodeKind::DecK, tokenList[cur].getLineShow());

    typeDef(t);
    varIDList(t);

    if (!match(LexType::SEMI))
        syntaxError("缺少符号：\";\"");

    t->sibling = varDecMore();

    return t;
}

TreeNode* ParserRecursiveDescent::varDecMore()
{
    TreeNode* t = nullptr;
    switch (tokenList[cur].getLexType()) {
        case LexType::PROCEDURE : break;
        case LexType::BEGIN : break;
        case LexType::INTEGER_T :
            t = varDecList();
            break;
        case LexType::CHAR_T :
            t = varDecList();
            break;
        case LexType::ARRAY :
            t = varDecList();
            break;
        case LexType::RECORD:
            t = varDecList();
            break;
        case LexType::ID :
            t = varDecList();
            break;
        default :
            syntaxError("出现预期外的符号：\"" + tokenList[cur].getSem() + "\"！");
            break;
    }
    return t;
}

void ParserRecursiveDescent::varIDList(TreeNode* t)
{
    if (!match(LexType::ID))
        syntaxError("缺少变量标识符！");

    t->name[t->idnum] = tokenList[cur-1].getSem();
    t->idnum ++;

    varIDMore(t);
}

void ParserRecursiveDescent::varIDMore(TreeNode* t)
{
    switch (tokenList[cur].getLexType()) {
        case LexType::SEMI : break;
        case LexType::COMMA :
            match(LexType::COMMA);
            varIDList(t);
            break;
        default :
            syntaxError("出现预期外的符号：\"" + tokenList[cur].getSem() + "\"！");
            break;
    }
}

TreeNode* ParserRecursiveDescent::procDecpart()
{
    TreeNode* t = nullptr;
    switch (tokenList[cur].getLexType()) {
        case LexType::BEGIN : break;
        case LexType::PROCEDURE :
            t = procDec();
            break;
        default :
            syntaxError("出现预期外的符号：\"" + tokenList[cur].getSem() + "\"！");
            break;
    }
    return t;
}

TreeNode* ParserRecursiveDescent::procDec()
{
    TreeNode* t = new TreeNode(NodeKind::ProcDecK, tokenList[cur].getLineShow());

    if (!match(LexType::PROCEDURE))
        syntaxError("缺少函数声明：\"procedure\"！");

    procName(t);

    if (!match(LexType::LPAREN))
        syntaxError("缺少符号：\"(\"！");

    paramList(t);

    if (!match(LexType::RPAREN))
        syntaxError("缺少符号：\")\"！");

    if (!match(LexType::SEMI))
        syntaxError("缺少符号：\";\"！");

    t->child[1] = procDecPart();
    t->child[2] = procBody();
    t->sibling = procDecMore();

    return t;
}

TreeNode* ParserRecursiveDescent::procDecMore()
{
    TreeNode* t = nullptr;
    switch (tokenList[cur].getLexType()) {
        case LexType::BEGIN : break;
        case LexType::PROCEDURE :
            t = procDec();
            break;
        default :
            syntaxError("出现预期外的符号：\"" + tokenList[cur].getSem() + "\"！");
            break;
    }
    return t;
}

void ParserRecursiveDescent::procName(TreeNode* t)
{
    if (!match(LexType::ID))
        syntaxError("缺少函数名标识符！");

    t->name[t->idnum] = tokenList[cur-1].getSem();
    t->idnum ++;
}

void ParserRecursiveDescent::paramList(TreeNode* t)
{
    TreeNode* p = nullptr;
    switch (tokenList[cur].getLexType()) {
        case LexType::RPAREN : break;
        case LexType::INTEGER_T :
            p = paramDecList();
            t->child[0] = p;
            break;
        case LexType::CHAR_T :
            p = paramDecList();
            t->child[0] = p;
            break;
        case LexType::ARRAY :
            p = paramDecList();
            t->child[0] = p;
            break;
        case LexType::RECORD :
            p = paramDecList();
            t->child[0] = p;
            break;
        case LexType::ID :
            p = paramDecList();
            t->child[0] = p;
            break;
        case LexType::VAR :
            p = paramDecList();
            t->child[0] = p;
            break;
        default :
            syntaxError("出现预期外的符号：\"" + tokenList[cur].getSem() + "\"！");
            break;
    }
}

TreeNode* ParserRecursiveDescent::paramDecList()
{
    TreeNode* t = param();
    t->sibling = paramMore();

    return t;
}

TreeNode* ParserRecursiveDescent::paramMore()
{
    TreeNode* t = nullptr;
    switch (tokenList[cur].getLexType()) {
        case LexType::RPAREN : break;
        case LexType::SEMI :
            match(LexType::SEMI);
            t = paramDecList();
            break;
        default :
            syntaxError("出现预期外的符号：\"" + tokenList[cur].getSem() + "\"！");
            break;
    }
    return t;
}

TreeNode* ParserRecursiveDescent::param()
{
    TreeNode* t = new TreeNode(NodeKind::DecK, tokenList[cur].getLineShow());
    switch (tokenList[cur].getLexType()) {
        case LexType::INTEGER_T :
            t->attr.ProcAttr.paramt = ParamType::valparamType;
            typeDef(t);
            formList(t);
            break;
        case LexType::CHAR_T :
            t->attr.ProcAttr.paramt = ParamType::valparamType;
            typeDef(t);
            formList(t);
            break;
        case LexType::ARRAY :
            t->attr.ProcAttr.paramt = ParamType::valparamType;
            typeDef(t);
            formList(t);
            break;
        case LexType::RECORD :
            t->attr.ProcAttr.paramt = ParamType::valparamType;
            typeDef(t);
            formList(t);
            break;
        case LexType::ID :
            t->attr.ProcAttr.paramt = ParamType::valparamType;
            typeDef(t);
            formList(t);
            break;
        case LexType::VAR :
            match(LexType::VAR);
            t->attr.ProcAttr.paramt = ParamType::varparamType;
            typeDef(t);
            formList(t);
            break;
        default :
            syntaxError("出现预期外的符号：\"" + tokenList[cur].getSem() + "\"！");
            break;
    }
    return t;
}

void ParserRecursiveDescent::formList(TreeNode* t)
{
    if (!match(LexType::ID))
        syntaxError("缺少参数标识符！");

    t->name[t->idnum] = tokenList[cur-1].getSem();
    t->idnum ++;

    fidMore(t);
}

void ParserRecursiveDescent::fidMore(TreeNode* t)
{
    switch (tokenList[cur].getLexType()) {
        case LexType::SEMI : break;
        case LexType::RPAREN : break;
        case LexType::COMMA :
            match(LexType::COMMA);
            formList(t);
            break;
        default:
            syntaxError("出现预期外的符号：\"" + tokenList[cur].getSem() + "\"！");
            break;
    }
}

TreeNode* ParserRecursiveDescent::procDecPart()
{
    TreeNode* t = declarePart();
    return t;
}

TreeNode* ParserRecursiveDescent::procBody()
{
    TreeNode* t = programBody();
    return t;
}

TreeNode* ParserRecursiveDescent::programBody()
{
    if (!match(LexType::BEGIN))
        syntaxError("缺少程序开始符：\"begin\"！");

    TreeNode* t= new TreeNode(NodeKind::StmLK, tokenList[cur].getLineShow());
    t->child[0] = stmList();

    if (!match(LexType::END))
        syntaxError("缺少程序结束符：\"end\"！");

    return t;
}

TreeNode* ParserRecursiveDescent::stmList()
{
    TreeNode* t = stm();
    TreeNode* p = stmMore();

    if (t != nullptr)
        t->sibling = p;

    return t;
}

TreeNode* ParserRecursiveDescent::stmMore()
{
    TreeNode* t = nullptr;
    switch (tokenList[cur].getLexType()) {
        case LexType::ELSE : break;
        case LexType::FI : break;
        case LexType::END : break;
        case LexType::ENDWH : break;
        case LexType::SEMI :
            match(LexType::SEMI);
            t = stmList();
            break;
        default :
            syntaxError("出现预期外的符号：\"" + tokenList[cur].getSem() + "\"！");
            break;
    }
    return t;
}

TreeNode* ParserRecursiveDescent::stm()
{
    TreeNode* t = nullptr;
    switch (tokenList[cur].getLexType()) {
        case LexType::IF :
            t = conditionalStm();
            break;
        case LexType::WHILE :
            t = loopStm();
            break;
        case LexType::READ :
            t = inputStm();
            break;
        case LexType::WRITE :
            t = outputStm();
            break;
        case LexType::RETURN :
            t = returnStm();
            break;
        case LexType::ID :
            match(LexType::ID);
            temp_name = tokenList[cur-1].getSem();
            t = assCall();
            break;
        default :
            syntaxError("出现预期外的符号：\"" + tokenList[cur].getSem() + "\"！");
            break;
    }
    return t;
}

TreeNode* ParserRecursiveDescent::assCall()
{
    TreeNode* t = nullptr;
    switch (tokenList[cur].getLexType()) {
        case LexType::ASSIGN :
        case LexType::LMIDPAREN :
        case LexType::DOT :
            t = assignmentRest();
            break;
        case LexType::LPAREN :
            t = callStmRest();
            break;
        default :
            syntaxError("出现预期外的符号：\"" + tokenList[cur].getSem() + "\"！");
            break;
    }
    return t;
}

TreeNode* ParserRecursiveDescent::assignmentRest()
{
    TreeNode* t = new TreeNode(NodeKind::StmtK, tokenList[cur].getLineShow());
    t->kind.stmt = StmtKind::AssignK;

    TreeNode* p = new TreeNode(NodeKind::ExpK, tokenList[cur].getLineShow());
    p->kind.exp = ExpKind::VariK;
    p->name[p->idnum] = temp_name;
    p->idnum ++;
    variMore(p);

    t->child[0] = p;

    if (!match(LexType::ASSIGN))
        syntaxError("缺少符号：\":=\"");

    t->child[1] = exp();

    return t;
}

TreeNode* ParserRecursiveDescent::conditionalStm()
{
    TreeNode* t = new TreeNode(NodeKind::StmtK, tokenList[cur].getLineShow());
    t->kind.stmt = StmtKind::IfK;

    if (!match(LexType::IF))
        syntaxError("缺少条件语句标志符：\"if\"！");

    t->child[0] = relExp();

    if (!match(LexType::THEN))
        syntaxError("缺少条件语句标志符：\"then\"！");

    t->child[1] = stmList();

    if (!match(LexType::ELSE))
        syntaxError("缺少条件语句标志符：\"else\"！");

    t->child[2] = stmList();

    if (!match(LexType::FI))
        syntaxError("缺少条件语句标志符：\"fi\"！");

    return t;
}

TreeNode* ParserRecursiveDescent::loopStm()
{
    TreeNode* t = new TreeNode(NodeKind::StmtK, tokenList[cur].getLineShow());
    t->kind.stmt = StmtKind::WhileK;

    if (!match(LexType::WHILE))
        syntaxError("缺少循环语句标志符：\"while\"！");

    t->child[0] = relExp();

    if (!match(LexType::DO))
        syntaxError("缺少循环语句标志符：\"do\"！");

    t->child[1] = stmList();

    if (!match(LexType::ENDWH))
        syntaxError("缺少循环语句标志符：\"endwh\"！");

    return t;
}

TreeNode* ParserRecursiveDescent::inputStm()
{
    TreeNode* t = new TreeNode(NodeKind::StmtK, tokenList[cur].getLineShow());
    t->kind.stmt = StmtKind::ReadK;

    if (!match(LexType::READ))
        syntaxError("缺少输入语句标志符：\"read\"！");

    if (!match(LexType::LPAREN))
        syntaxError("缺少符号：\"(\"！");

    inVar(t);

    if (!match(LexType::RPAREN))
        syntaxError("缺少符号：\")\"！");

    return t;
}

void ParserRecursiveDescent::inVar(TreeNode* t)
{
    if (!match(LexType::ID))
        syntaxError("缺少输入标识符！");

    t->name[t->idnum] = tokenList[cur-1].getSem();
    t->idnum ++;
}

TreeNode* ParserRecursiveDescent::outputStm()
{
    TreeNode* t = new TreeNode(NodeKind::StmtK, tokenList[cur].getLineShow());
    t->kind.stmt = StmtKind::WriteK;

    if (!match(LexType::WRITE))
        syntaxError("缺少输出语句标志符：\"write\"！");

    if (!match(LexType::LPAREN))
        syntaxError("缺少符号：\"(\"！");

    t->child[0] = exp();

    if (!match(LexType::RPAREN))
        syntaxError("缺少符号：\")\"！");

    return t;
}

TreeNode* ParserRecursiveDescent::returnStm()
{
    TreeNode* t = new TreeNode(NodeKind::StmtK, tokenList[cur].getLineShow());
    t->kind.stmt = StmtKind::ReturnK;

    if (!match(LexType::RETURN))
        syntaxError("缺少返回语句标志符：\"return\"！");

    return t;
}

TreeNode* ParserRecursiveDescent::callStmRest()
{
    TreeNode* t = new TreeNode(NodeKind::StmtK, tokenList[cur].getLineShow());
    t->kind.stmt = StmtKind::CallK;

    if (!match(LexType::LPAREN))
        syntaxError("缺少符号：\"(\"！");

    TreeNode* p = new TreeNode(NodeKind::ExpK, tokenList[cur].getLineShow());
    p->kind.exp = ExpKind::VariK;
    p->name[p->idnum] = temp_name;
    p->idnum ++;
    t->child[0] = p;

    t->child[1] = actParamList();

    if (!match(LexType::RPAREN))
        syntaxError("缺少符号：\")\"！");

    return t;
}

TreeNode* ParserRecursiveDescent::actParamList()
{
    TreeNode* t = nullptr;
    switch (tokenList[cur].getLexType()) {
        case LexType::RPAREN : break;
        case LexType::ID :
            t = exp();
            if (t != nullptr)
                t->sibling = actParamMore();
            break;
        case LexType::INTC_VAL :
            t = exp();
            if (t != nullptr)
                t->sibling = actParamMore();
            break;
        default :
            syntaxError("出现预期外的符号：\"" + tokenList[cur].getSem() + "\"！");
            break;
    }
    return t;
}

TreeNode* ParserRecursiveDescent::actParamMore()
{
    TreeNode* t = nullptr;
    switch (tokenList[cur].getLexType()) {
        case LexType::RPAREN : break;
        case LexType::COMMA :
            match(LexType::COMMA);
            t = actParamList();
            break;
        default:
            syntaxError("出现预期外的符号：\"" + tokenList[cur].getSem() + "\"！");
            break;
    }
    return t;
}

TreeNode* ParserRecursiveDescent::relExp()
{
    TreeNode* t = exp();

    if (tokenList[cur].getLexType() == LexType::LT || tokenList[cur].getLexType() == LexType::EQ) {
        TreeNode* p = new TreeNode(NodeKind::ExpK, tokenList[cur].getLineShow());
        p->kind.exp = ExpKind::OpK;

        p->child[0] = t;
        cmpOp(p);
        p->child[1] = exp();

        t = p;
    }

    return t;
}

TreeNode* ParserRecursiveDescent::exp()
{
    TreeNode* t = term();

    while (tokenList[cur].getLexType() == LexType::PLUS || tokenList[cur].getLexType() == LexType::MINUS) {
        TreeNode* p = new TreeNode(NodeKind::ExpK, tokenList[cur].getLineShow());
        p->kind.exp = ExpKind::OpK;

        p->child[0] = t;
        addOp(p);
        t = p;

        t->child[1] = term();
    }

    return t;
}

TreeNode* ParserRecursiveDescent::term()
{
    TreeNode* t = factor();

    if (tokenList[cur].getLexType() == LexType::TIMES || tokenList[cur].getLexType() == LexType::DIVIDE) {
        TreeNode* p = new TreeNode(NodeKind::ExpK, tokenList[cur].getLineShow());
        p->kind.exp = ExpKind::OpK;

        p->child[0] = t;
        multOp(p);
        p->child[1] = factor();

        t = p;
    }

    return t;
}

TreeNode* ParserRecursiveDescent::factor()
{
    TreeNode* t = nullptr;
    switch (tokenList[cur].getLexType()) {
        case LexType::INTC_VAL :
            t = new TreeNode(NodeKind::ExpK, tokenList[cur].getLineShow());
            t->kind.exp = ExpKind::ConstK;

            match(LexType::INTC_VAL);
            t->attr.ExpAttr.val = tokenList[cur-1].getSem().toInt();

            break;
        case LexType::ID :
            t = variable();
            break;
        case LexType::LPAREN :
            match(LexType::LPAREN);
            t = exp();

            if (!match(LexType::RPAREN))
                syntaxError("缺少符号：\")\"");

            break;
        default :
            syntaxError("出现预期外的符号：\"" + tokenList[cur].getSem() + "\"！");
            break;
    }
    return t;
}

TreeNode* ParserRecursiveDescent::variable()
{
    TreeNode* t = new TreeNode(NodeKind::ExpK, tokenList[cur].getLineShow());
    t->kind.exp = ExpKind::VariK;

    if (!match(LexType::ID))
        syntaxError("缺少变量标识符！");

    t->name[t->idnum] = tokenList[cur-1].getSem();
    t->idnum ++;

    variMore(t);

    return t;
}

void ParserRecursiveDescent::variMore(TreeNode* t)
{
    switch (tokenList[cur].getLexType()) {
        case LexType::ASSIGN : break;
        case LexType::TIMES : break;
        case LexType::EQ : break;
        case LexType::LT : break;
        case LexType::PLUS : break;
        case LexType::MINUS : break;
        case LexType::DIVIDE : break;
        case LexType::RPAREN : break;
        case LexType::RMIDPAREN : break;
        case LexType::SEMI : break;
        case LexType::COMMA : break;
        case LexType::THEN : break;
        case LexType::ELSE : break;
        case LexType::FI : break;
        case LexType::DO : break;
        case LexType::ENDWH : break;
        case LexType::END : break;
        case LexType::LMIDPAREN :
            match(LexType::LMIDPAREN);

            t->child[0] = exp();
            t->attr.ExpAttr.varkind = VarKind::ArrayMembV;
            t->child[0]->attr.ExpAttr.varkind = VarKind::IdV;

            if (!match(LexType::RMIDPAREN))
                syntaxError("缺少符号：\"]\"！");

            break;
        case LexType::DOT :
            match(LexType::DOT);

            t->child[0] = fieldVar();
            t->attr.ExpAttr.varkind = VarKind::FieldMembV;
            t->child[0]->attr.ExpAttr.varkind = VarKind::IdV;

            break;
        default :
            syntaxError("出现预期外的符号：\"" + tokenList[cur].getSem() + "\"！");
            break;
    }
}

TreeNode* ParserRecursiveDescent::fieldVar()
{
    TreeNode* t = new TreeNode(NodeKind::ExpK, tokenList[cur].getLineShow());
    t->kind.exp = ExpKind::VariK;

    if (!match(LexType::ID))
        syntaxError("缺少变量标识符！");

    t->name[t->idnum] = tokenList[cur-1].getSem();
    t->idnum ++;

    fieldVarMore(t);

    return t;
}

void ParserRecursiveDescent::fieldVarMore(TreeNode* t)
{
    switch (tokenList[cur].getLexType()) {
        case LexType::ASSIGN : break;
        case LexType::TIMES : break;
        case LexType::EQ : break;
        case LexType::LT : break;
        case LexType::PLUS : break;
        case LexType::MINUS : break;
        case LexType::DIVIDE : break;
        case LexType::RPAREN : break;
        case LexType::SEMI : break;
        case LexType::COMMA : break;
        case LexType::THEN : break;
        case LexType::ELSE : break;
        case LexType::FI : break;
        case LexType::DO : break;
        case LexType::ENDWH : break;
        case LexType::END : break;
        case LexType::LMIDPAREN :
            match(LexType::LMIDPAREN);

            t->child[0] = exp();
            t->child[0]->attr.ExpAttr.varkind = VarKind::ArrayMembV;

            if (!match(LexType::RMIDPAREN))
                syntaxError("缺少符号：\")\"！");

            break;
        default:
            syntaxError("出现预期外的符号：\"" + tokenList[cur].getSem() + "\"！");
            break;
    }
}

void ParserRecursiveDescent::cmpOp(TreeNode* t)
{
    if (match(LexType::LT))
        t->attr.ExpAttr.op = LexType::LT;
    else if (match(LexType::EQ))
        t->attr.ExpAttr.op = LexType::EQ;
    else
        syntaxError("缺少比较运算符！");
}

void ParserRecursiveDescent::addOp(TreeNode* t)
{
    if (match(LexType::PLUS))
        t->attr.ExpAttr.op = LexType::PLUS;
    else if (match(LexType::MINUS))
        t->attr.ExpAttr.op = LexType::MINUS;
    else
        syntaxError("缺少加减运算符！");
}

void ParserRecursiveDescent::multOp(TreeNode* t)
{
    if (match(LexType::TIMES))
        t->attr.ExpAttr.op = LexType::TIMES;
    else if (match(LexType::DIVIDE))
        t->attr.ExpAttr.op = LexType::DIVIDE;
    else
        syntaxError("缺少乘除运算符！");
}

void ParserRecursiveDescent::syntaxError(QString error)
{
    QString msg = QString("第%1行  出现语法错误：%2").arg(QString::number(tokenList[cur].getLineShow())).arg(error);
    QMessageBox::critical(nullptr, "错误", msg);
    exit(-1);
}
























