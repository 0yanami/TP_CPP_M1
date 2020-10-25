#ifndef TOKENSH
#define TOKENSH

#include<string>

using namespace std;
class Token{
    int eval();
};

class Number : public Token{
    Number(string _t){
        num = 3;
    }
    int eval(){

    }
    int num;
};

class BinOp : public Token{

};














#endif