#ifndef TOKENSH
#define TOKENSH

#include<string>
#include <iostream>

using namespace std;
class Token{
public:
    virtual int eval() = 0;
    virtual void print(ostream& os) const = 0;
    friend ostream& operator<<(ostream& os, const Token& t);
};

class Literal : public Token{
private:
    int num;
public:
    Literal(int _num) : num(_num){}
    int eval() override{
        return 0;
    }
    void print(ostream& os) const override {
        os << "Numeral(" << num << ")";
    }
};

class BinOp : public Token{
private:
    char op;
public:
    BinOp(char _op) : op(_op){}
    int eval() override {
        return 0;
    }
    void print(ostream& os) const override{
        os << "Operateur(" << op << ")";
    }
};

#endif