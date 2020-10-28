#ifndef TOKENSH
#define TOKENSH

#include <string>
#include <iostream>
#include <map>
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
    DIV  = '/',
    LPAR = '(',
    RPAR = ')'
};

//list of possible associativities (RIGHT is not needed "right" now)
enum ASSO {
    LEFT,
    NONE
};

//Token Properties TOKEN -> PRIORITY(0=low), ASSOCIATIVITY
const map<TOKEN,tuple<int,ASSO>> tkProp = {
    {TOKEN::NUM,{0,ASSO::NONE}},
    {TOKEN::ADD,{1,ASSO::LEFT}},
    {TOKEN::SUB,{1,ASSO::LEFT}},
    {TOKEN::MUL,{2,ASSO::LEFT}},
    {TOKEN::DIV,{2,ASSO::LEFT}},
    {TOKEN::LPAR,{3,ASSO::NONE}},
    {TOKEN::RPAR,{3,ASSO::NONE}}
};

class Token {
public:
    virtual ~Token(){};
    virtual TOKEN getTk() = 0;
    virtual int eval() = 0;
    virtual void print(ostream &os) const = 0;
    virtual void RPN(vector<Token*> &output, vector<Token*> &stack) = 0;
    friend ostream &operator<<(ostream &os, const Token &t);
};

class Literal : public Token{
private:
    TOKEN t;
    int num;
public:
    TOKEN getTk() override {return t;}
    Literal(int _num) : num(_num) {
        t = TOKEN::NUM;
    }
    int eval() override
    {
        return 0;
    }
    void print(ostream &os) const override
    {
        os << "Numeral(" << num << ")";
    }
    void RPN(vector<Token*> &output, vector<Token*> &stack) override
    {
        output.push_back(this);
    }
};

class BinOp : public Token
{
private:
    TOKEN t;
    inline bool gtPrec(Token* token){
        return (get<0>(tkProp.at(token->getTk()))  > get<0>(tkProp.at(t)));
    };
    //the operator has equal precedence and the token is left associative
    inline bool eqPrecLasso(Token* token){
        return (get<0>(tkProp.at(token->getTk())) == t) && 
        (get<1>(tkProp.at(token->getTk())) == ASSO::LEFT);
    };
    //the operator is a left parenthesis
    inline bool isLPar(Token* token){
        return (token->getTk() == TOKEN::LPAR);
    };
public:
    BinOp(TOKEN _t) : t(_t) {}
    TOKEN getTk() override {return t;}
    int eval() override
    {
        return 0;
    }
    void print(ostream &os) const override
    {
        os << "Operateur(" << (char)t << ")";
    }

    void RPN(vector<Token*>& output, vector<Token*>& stack) override{ 
        while (!stack.empty() && (gtPrec(stack.back()) || eqPrecLasso(stack.back())) && !isLPar(stack.back())){
            output.push_back(move(stack.back()));
            stack.pop_back();
        }
        stack.push_back(this);
    }
};

#endif