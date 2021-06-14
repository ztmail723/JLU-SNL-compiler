#include "lexerimp.h"
#include <QDebug>

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

int LexerImp::getCharType(QChar c){
    if((c >= "a" && c <= "z") || (c >= "A" && c <= "Z")){
        //判断标识符和关键字
        return 1;
    }
    if(c >= "0" && c <= "9"){
        return 2;
    }
    if(c == "<" || c == "+" || c == "-"
            || c == "*" || c == "/" || c == "(" || c == ")"
            || c == ";" || c == "," || c == "[" || c == "]"){
        return 3;
    }
    if(c == "."){
        return 4;
    }
    if(c == ":"){
        return 5;
    }
    if(c == "="){
        return 6;
    }
    if(c == "\n"){
        return 7;
    }
   return 0;
}

QList<QString> LexerImp::pushString(QList<QString> strQueue, QString str){
    QString _str = str;
    strQueue.push_back(str);
    return strQueue;
}

TokenList* LexerImp::queueToList(TokenList* tokenList, QList<QString> strQueue){
    int lineShow = 1;
    while (!strQueue.isEmpty()) {
        if(getCharType(strQueue.front()[0]) == 1){
            if(isKeyWord(strQueue.front())){
                tokenList = appendTokenList(tokenList, lineShow, getLexType(strQueue.front()), "-1");
            }else {
                tokenList = appendTokenList(tokenList, lineShow, getLexType("ID"), strQueue.front());
            }
        }
        if(getCharType(strQueue.front()[0]) == 2){
            tokenList = appendTokenList(tokenList, lineShow, getLexType("INTC_VAL"), strQueue.front());
        }
        if(getCharType(strQueue.front()[0]) == 3
                || getCharType(strQueue.front()[0]) == 4
                || getCharType(strQueue.front()[0]) == 5
                || getCharType(strQueue.front()[0]) == 6){
            tokenList = appendTokenList(tokenList, lineShow, getLexType(strQueue.front()), "-1");
        }
        if(strQueue.front() == ".." || strQueue.front() == ":="){
            tokenList = appendTokenList(tokenList, lineShow, getLexType(strQueue.front()), "-1");
        }
        if(getCharType(strQueue.front()[0]) == 7)lineShow++;
        strQueue.pop_front();
    }
    return tokenList;
}

TokenList* LexerImp::run1(QString str){
    TokenList* tokenList = new TokenList();
    /* 在下边实现 */
    int lineShow = 1;
    int strp = 0;//str的下标
    QString temp;//记录保留字或者变量
    QString last = "";
    QChar c;
    while(strp < str.length()){
        if((last >= "a" && last <= "z")
                || (last >= "A" && last <= "Z")){
            //判断标识符和关键字
            temp += last;
            if((str[strp] >= "a" && str[strp] <= "z")
                    || (str[strp] >= "A" && str[strp] <= "Z")){
            }else {
                if (isKeyWord(temp)) {
                    tokenList = appendTokenList(tokenList, lineShow, getLexType(temp), "-1");
                }else {
                    tokenList = appendTokenList(tokenList, lineShow, getLexType("ID"), temp);
                }
                temp = "";
            }
        }
        if(last >= "0" && last <= "9"){
            temp += last;
            if(str[strp] < "0" && str[strp] > "9"){
                tokenList = appendTokenList(tokenList, lineShow, getLexType("INTC_VAL"), temp);
                temp = "";
            }
        }
        if(last == "="){
            c = last[0];
            tokenList = appendTokenList(tokenList, lineShow, getLexType(c), "-1");
        }
        if(last == "<"){
            c = last[0];
            tokenList = appendTokenList(tokenList, lineShow, getLexType(c), "-1");
        }
        if(last == "+"){
            c = last[0];
            tokenList = appendTokenList(tokenList, lineShow, getLexType(c), "-1");
        }
        if(last == "-"){
            c = last[0];
            tokenList = appendTokenList(tokenList, lineShow, getLexType(c), "-1");
        }
        if(last == "*"){
            c = last[0];
            tokenList = appendTokenList(tokenList, lineShow, getLexType(c), "-1");
        }
        if(last == "/"){
            c = last[0];
            tokenList = appendTokenList(tokenList, lineShow, getLexType(c), "-1");
        }
        if(last == "("){
            c = last[0];
            tokenList = appendTokenList(tokenList, lineShow, getLexType(c), "-1");
        }
        if(last == ")"){
            c = last[0];
            tokenList = appendTokenList(tokenList, lineShow, getLexType(c), "-1");
        }
        if(last == "."){
            c = last[0];
            if(str[strp] == "."){
                tokenList = appendTokenList(tokenList, lineShow, getLexType(".."), "-1");
            }
            tokenList = appendTokenList(tokenList, lineShow, getLexType(c), "-1");
        }
        if(last == ":"){
            c = last[0];
            if(str[strp] == "="){
                tokenList = appendTokenList(tokenList, lineShow, getLexType(":="), "-1");
            }
            tokenList = appendTokenList(tokenList, lineShow, getLexType(c), "-1");
        }
        if(last == ";"){
            c = last[0];
            tokenList = appendTokenList(tokenList, lineShow, getLexType(c), "-1");
        }
        if(last == ","){
            c = last[0];
            tokenList = appendTokenList(tokenList, lineShow, getLexType(c), "-1");
        }
        if(last == "["){
            c = last[0];
            tokenList = appendTokenList(tokenList, lineShow, getLexType(c), "-1");
        }
        if(last == "]"){
            c = last[0];
            tokenList = appendTokenList(tokenList, lineShow, getLexType(c), "-1");
        }
        if(last == "\n"){
            lineShow++;
        }
        last = str[strp];
        strp++;
    }
    return tokenList;
}


//state状态：1，9标识符状态
//          2，10数字状态
//          3（单分界符）完成状态
//          4（“.”）单分界符
//          5（“:”）单分界符
//          6（“..”）数组下标界限状态
//          7（“\n”）换行
//          8（“:=”）赋值状态
//          9结束状态

TokenList* LexerImp::run(QString str)
{
    TokenList* tokenList = new TokenList();
    /* 在下边实现 */qDebug() <<"*****************";
    QList<QString> strQuene;
    int strp = 0;       //str的下标
    QString temp = "";  //记录保留字或者变量
    int state = 0;      //自动机状态
    int flag = 0;       //清空字符串标志
    while(strp < str.length()){
        if(flag == 1){
            strQuene = pushString(strQuene, temp);
            temp = "";
            flag = 0;
        }
        switch (state) {
        case 0 :
            switch (getCharType(str[strp])) {
            case 1 : state = 1; break;
            case 2 : state = 2; break;
            case 3 : state = 3; break;
            case 4 : state = 4; break;
            case 5 : state = 5; break;
            case 6 : state = 6; break;
            case 7 : state = 7; break;
            default: state = 9;
            }
            break;
        case 1 : state = 0;temp += str[strp];strp++;break;
        case 2 : state = 0;temp += str[strp];strp++;break;
        case 3 : state = 9;break;
        case 4 : state = 8;flag = 1;break;//“.”
        case 5 : state = 6;flag = 1;break;//“:”
        //判断：“:=”和“:”
        case 6 :
            temp += str[strp];
            strp++;
            if(getCharType(str[strp]) == 6)temp += str[strp ];
            flag = 1;
            state = 0;
            break;
        case 7 : state = 9;break;
        //判断：“..”和“.”
        case 8 :
            temp += str[strp];
            strp++;
            if(getCharType(str[strp]) == 4)temp += str[strp];
            flag = 1;
            state = 0;
            break;
        case 9 :
            strQuene = pushString(strQuene, temp);
            temp = "";
            temp += str[strp];
            flag = 1;
            state = 0;
            strp++;
            break;
        }
    }
    tokenList = queueToList(tokenList, strQuene);
    return tokenList;
}

