#ifndef TOKENSH
#define TOKENSH

#include <string>
#include <iostream>
#include <map>
#include <sstream>
#include <tuple>
#include <memory>
#include <vector>

using namespace std;

//list of token
enum TOKEN {
    NUM  = '_',
    ADD  = '+',
    SUB  = '-',
    MUL  = '*',
    DIV  = '/'
};

//list of possible associativities (RIGHT is not needed "right" now)
enum ASSO {
    LEFT,
    NONE
};

//Token Properties TOKEN -> PRIORITY(0=low), ASSOCIATIVITY
const map<TOKEN,tuple<int,ASSO>> tkProp = {
    {TOKEN::NUM,{1,ASSO::NONE}},
    {TOKEN::ADD,{2,ASSO::LEFT}},
    {TOKEN::SUB,{2,ASSO::LEFT}},
    {TOKEN::MUL,{3,ASSO::LEFT}},
    {TOKEN::DIV,{4,ASSO::LEFT}}
};

class Token {
public:
    virtual ~Token(){};
    virtual TOKEN getTk() = 0;
    virtual float v() const = 0;
    virtual void eval(vector<Token*>& stack) = 0;
    virtual void print(ostream &os) const = 0;
    virtual void RPN(vector<Token*> &output, vector<Token*> &stack) = 0;
    friend ostream &operator<<(ostream &os, const Token &t);
};

class Literal : public Token{
private:
    TOKEN t;
    float num;
public:
    TOKEN getTk() override {return t;}
    Literal(float _num) : num(_num) {
        t = TOKEN::NUM;
    }
    //valeur du Literal
    float v() const override{
        return num;
    }
    void eval(vector<Token*>& stack) override {
        stack.push_back(this);
    }
    void print(ostream &os) const override{
        os << "Numeral(" << v() << ")";
    }
    void RPN(vector<Token*> &output, vector<Token*> &stack) override{
        output.push_back(this);
    }
};

class BinOp : public Token
{
private:
    TOKEN t;
    inline bool gtEqPrec(Token* token) const { //TODO: add const
        return (get<0>(tkProp.at(token->getTk()))  >= get<0>(tkProp.at(t)));
    };
    float compute(Literal* a,Literal* b){
        switch(t){
            case ADD:return a->v() + b->v(); 
            case SUB:return a->v() - b->v();
            case MUL:return a->v() * b->v(); 
            case DIV:return a->v() / b->v();
        };
    }
public:
    float v() const  override{
        return -1;
    }
    BinOp(TOKEN _t) : t(_t) {}
    TOKEN getTk() override {return t;}
    void eval(vector<Token*>& stack) override {
        Literal* b = static_cast<Literal*>(stack.back());
        stack.pop_back();
        Literal* a = static_cast<Literal*>(stack.back());
        stack.pop_back();
        stack.push_back(new Literal(compute(a,b)));
    }
    void print(ostream &os) const override{
        os << "Operateur(" << (char)t << ")";
    }
    void RPN(vector<Token*>& output, vector<Token*>& stack) override{
        while (!stack.empty() && gtEqPrec(stack.back())){
            output.push_back(move(stack.back()));
            stack.pop_back();
        }
        stack.push_back(this);
    }
};
#endif