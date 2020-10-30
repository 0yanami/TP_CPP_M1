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
    LIT  = '_',
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
    {TOKEN::LIT,{1,ASSO::NONE}},
    {TOKEN::ADD,{2,ASSO::LEFT}},
    {TOKEN::SUB,{2,ASSO::LEFT}},
    {TOKEN::MUL,{3,ASSO::LEFT}},
    {TOKEN::DIV,{4,ASSO::LEFT}},
    {TOKEN::LPAR,{0,ASSO::NONE}},
    {TOKEN::RPAR,{0,ASSO::NONE}}
};

class Token {
public:
    virtual ~Token(){};//TODO:faire un destructeur avec print pour chaque type de token pour voir les destructions
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
    ~Literal(){ cout << "literal"<<num<<" destructed" << endl;}
    Literal(float _num) : num(_num) {
        cout << "literal"<<num<<" constructed"<< endl;
        t = TOKEN::LIT;
    }
    TOKEN getTk() override {return t;}
    
    //valeur du Literal
    float v() const override{
        return num;
    }
    void eval(vector<Token*>& stack) override {
        stack.push_back(new Literal(num));
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
    inline bool isLpar(Token* token) const {
        return token->getTk() == LPAR;
    }
    float compute(float a,float b){
        switch(t){
            case ADD:return a + b; 
            case SUB:return a - b;
            case MUL:return a * b; 
            case DIV:return a / b;
        };
    }
public:
    ~BinOp(){ cout << "Binop "<<(char)t<<" destructed" << endl;}
    float v() const  override{
        
        return -1;
    }
    BinOp(TOKEN _t) : t(_t) {cout << "Binop "<<(char)_t<<" constructed" << endl;}
    TOKEN getTk() override {return t;}

    void eval(vector<Token*>& stack) override {
        float b = stack.back()->v();
        delete stack.back();
        stack.pop_back();
        float a =stack.back()->v();
        delete stack.back();
        stack.pop_back();
        float res = compute(a,b);
        stack.push_back(new Literal(res));
    }
    void print(ostream &os) const override{
        os << "Operateur(" << (char)t << ")";
    }
    void RPN(vector<Token*>& output, vector<Token*>& stack) override{
        while (!stack.empty() && gtEqPrec(stack.back()) && !isLpar(stack.back())){
            output.push_back(move(stack.back()));
            stack.pop_back();
        }
        stack.push_back(this);
    }
};

class Par : public Token
{
private:
    TOKEN t;
public:
    Par(TOKEN _t): t(_t){cout << "Parenthesis "<<(char)_t<<" constructed" << endl;}
    ~Par(){ cout << "Parenthesis "<<(char)t<<" destructed" << endl;}
    TOKEN getTk() override {return t;}
    //valeur du Literal
    float v() const override{
        return -1;
    }
    void eval(vector<Token*>& stack) override {
        stack.push_back(this);
    }
    void print(ostream &os) const override{
        os << (t==LPAR?"(Left":"(Right") <<"Parenthesis)";
    }
    void RPN(vector<Token*> &output, vector<Token*> &stack) override{
        if(!stack.empty()){
            cout << "entrée: " ;
            for(auto& tk : stack){
                cout  << (char)tk->getTk() << " ";
            } 
            cout << endl;
        }
        //(11+1(()
        if(t == LPAR){
            stack.push_back(this);
        }
        else if(t == RPAR){
            if(stack.empty()){
                    throw invalid_argument( "Input string contains mismatched parenthesis");
            }
            cout << "test2"<< endl;
            while(stack.back()->getTk() != LPAR){
                if(stack.empty()){
                    throw invalid_argument( "Input string contains mismatched parenthesis");
                }
                output.push_back(move(stack.back()));
                stack.pop_back();
            }
            if(stack.back()->getTk() == LPAR){
                stack.pop_back();
            }
        }
    }
};

#endif