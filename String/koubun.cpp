#include <iostream>
#include <string>
#include <cctype>

using namespace std;
typedef string::const_iterator State;
/*
<四則演算の式> ::= <乗算除算の式> (+ or -) <乗算除算の式> (+ or -) ...
<乗算除算の式> ::= <数> (* or /) <数> (* or /) ...
<数>           ::= ...
 とみて、下から渡していく。
 */

int number(State &begin){
    char ret='A';
    while(isupper(*begin)){
        ret=*begin;
        begin++;
    }
    return ret;
}
int term(State &begin){
    int ret=number(begin);
    for(;;){
        if(*begin=='*'){
            begin++;
            ret*=number(begin);
        }else if(*begin){
            begin++;
            ret/=number(begin);
        }else  break;
    }
    return ret;
}
int expression(State &begin){
    int ret=term(begin);
    for(;;){
        if(*begin=='+'){
            begin++;
            ret+=term(begin);
        }else if(*begin=='-'){
            begin++;
            ret-=term(begin);
        }else break;
    }
    return ret;
}
/*
 括弧列で優先度を変更するなら、
 <四則演算の式> ::= <乗算除算の式> (+ or -) <乗算除算の式> (+ or -) ...
 <乗算除算の式> ::= <括弧か数> (* or /) <括弧か数> (* or /) ...
 <括弧か数>     ::= '(' <四則演算の式> ')' or <数>
 <数>           ::= ...
 と構文を変更　　括弧か数を返すfactorを作る
 */

int factor(State &begin){
    if(*begin=='('){
        begin++;
        int ret=expression(begin);
        begin++;
    }else{
        return  number(begin);
    }
}
int NOT(int a){
    return 2-a;
}
int AND(int a,int b){
    if(a==0||b==0) return 0;
    if(a==1||b==1) return 1;
    return  2;
}
int OR(int a,int b){
    if(a==2||b==2) return 2;
    if(a==1||b==1) return 1;
    return 0;
}
int number(State &begin){
    int ret=0;
    if(isdigit(*begin)){
        ret=(*begin-'0');
        begin++;
    }
    return ret;
}
int factor(State &begin){
    if(*begin=='('){
        begin++;
        int ret=expression(begin);
        begin++;
        return ret;
    }else if(*begin=='-'){
        begin++;
        return NOT(factor(begin));
    }else{
        return number(begin);
    }
}
int expression(State &begin){
    int ret=factor(begin);
    for(;;){
        if(*begin=='+'){
            begin++;
            ret=OR(ret,factor(begin));
        }else if(*begin=='*'){
            begin++;
            ret=AND(ret,factor(begin));
        }else break;
    }
    return ret;
}
