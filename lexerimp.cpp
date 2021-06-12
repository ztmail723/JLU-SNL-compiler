#include "lexerimp.h"

LexerImp::LexerImp()
{

}

bool LexerImp::isKeyWord(QString str){
    //判断字符串是否为关键字
    if(ConstantVar::reservedWords.contains(str)){
        return true;
    }
    return false;
}

LexType LexerImp::getLexType(QString str){
    QMap<LexType, QString>::const_iterator it_1;
    QMap<QString, LexType>::const_iterator it_2;
    //保留字迭代器
    for (it_1 = ConstantVar::lexName.constBegin();
         it_1 != ConstantVar::lexName.constEnd(); ++it_1) {
        if(str == it_1.value()){
            return it_1.key();
        }
    }
    for (it_2 = ConstantVar::reservedWords.constBegin();
         it_2 != ConstantVar::reservedWords.constEnd(); ++it_2) {
        if(str == it_2.key()){
            return it_2.value();
        }
    }
}

TokenList* LexerImp::appendTokenList(TokenList* tokenlist, int _lineShow, LexType _lex, QString _sem){
    Token token(_lineShow, _lex, _sem);
    tokenlist->append(token);
    QString lexStr = ConstantVar::lexName[token.getLexType()];
    return tokenlist;
    //栈区读入元素，当栈区清空时，导致tokenlist出现错误
}

TokenList* LexerImp::run(QString str)
{
    TokenList* tokenList = new TokenList();
    /* 在下边实现 */
    int lineShow = 1;
    int strp = 0;//str的下标
    QString temp;//记录保留字或者变量
    QChar c;
    while(strp < str.length()){
        if((str[strp] >= "a" && str[strp] <= "z")
                || (str[strp] >= "A" && str[strp] <= "Z")){
            //判断标识符和关键字
            temp += str[strp];
            strp++;

            while(((str[strp] >= "a" && str[strp] <= "z")
                  || (str[strp] >= "A" && str[strp] <= "Z")
                  || (str[strp] >= "0" && str[strp] <= "9")) && strp < str.length()){

                temp += str[strp];
                strp++;
            }

            if (isKeyWord(temp)) {

                tokenList = appendTokenList(tokenList, lineShow, getLexType(temp), "-1");
            }else {
                tokenList = appendTokenList(tokenList, lineShow, getLexType("ID"), temp);
            }
            temp = "";
            continue;
        }
        if(str[strp] >= "0" && str[strp] <= "9"){
            temp += str[strp];
            strp++;
            while((str[strp] >= "0" && str[strp] <= "9") && strp < str.length()){
                temp += str[strp];
                strp++;
            }
            tokenList = appendTokenList(tokenList, lineShow, getLexType("INTC_VAL"), temp);
            temp = "";
            continue;
        }
        if(str[strp] == "="){
            c = str[strp];
            tokenList = appendTokenList(tokenList, lineShow, getLexType(c), "-1");
            strp++;
            continue;
        }
        if(str[strp] == "<"){
            c = str[strp];
            tokenList = appendTokenList(tokenList, lineShow, getLexType(c), "-1");
            strp++;
            continue;
        }
        if(str[strp] == "+"){
            c = str[strp];
            tokenList = appendTokenList(tokenList, lineShow, getLexType(c), "-1");
            strp++;
            continue;
        }
        if(str[strp] == "-"){
            c = str[strp];
            tokenList = appendTokenList(tokenList, lineShow, getLexType(c), "-1");
            strp++;
            continue;
        }
        if(str[strp] == "*"){
            c = str[strp];
            tokenList = appendTokenList(tokenList, lineShow, getLexType(c), "-1");
            strp++;
            continue;
        }
        if(str[strp] == "/"){
            c = str[strp];
            tokenList = appendTokenList(tokenList, lineShow, getLexType(c), "-1");
            strp++;
            continue;
        }
        if(str[strp] == "("){
            c = str[strp];
            tokenList = appendTokenList(tokenList, lineShow, getLexType(c), "-1");
            strp++;
            continue;
        }
        if(str[strp] == ")"){
            c = str[strp];
            tokenList = appendTokenList(tokenList, lineShow, getLexType(c), "-1");
            strp++;
            continue;
        }
        if(str[strp] == "."){
            if(strp + 1 >= str.length())break;
            if(str[strp + 1] == "."){
                tokenList = appendTokenList(tokenList, lineShow, getLexType(".."), "-1");
                strp += 2;
                continue;
            }
            c = str[strp];
            tokenList = appendTokenList(tokenList, lineShow, getLexType(c), "-1");
            strp++;
            continue;
        }
        if(str[strp] == ":"){
            if(strp + 1 >= str.length())break;
            if(str[strp + 1] == "="){
                tokenList = appendTokenList(tokenList, lineShow, getLexType(":="), "-1");
                strp += 2;
                continue;
            }
            tokenList = appendTokenList(tokenList, lineShow, getLexType("COLON"), "-1");
            strp++;
            continue;
        }
        if(str[strp] == ";"){
            c = str[strp];
            tokenList = appendTokenList(tokenList, lineShow, getLexType(c), "-1");
            strp++;
            continue;
        }
        if(str[strp] == ","){
            c = str[strp];
            tokenList = appendTokenList(tokenList, lineShow, getLexType(c), "-1");
            strp++;
            continue;
        }
        if(str[strp] == "["){
            c = str[strp];
            tokenList = appendTokenList(tokenList, lineShow, getLexType(c), "-1");
            strp++;
            continue;
        }
        if(str[strp] == "]"){
            c = str[strp];
            tokenList = appendTokenList(tokenList, lineShow, getLexType(c), "-1");
            strp++;
            continue;
        }
        if(str[strp] == "\n"){
            lineShow++;
            strp++;
            continue;
        }
        strp++;
    }
    return tokenList;
}

