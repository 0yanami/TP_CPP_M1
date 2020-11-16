#ifndef TOKENSH
#define TOKENSH

#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>
#include <functional>

using namespace std;

// list of token supported by the language
enum TOKEN {
    LIT = '_',  // Litteral
    VAR = '$',  // Variable
    ADD = '+',
    SUB = '-',
    MUL = '*',
    DIV = '/',
    LPAR = '(',
    RPAR = ')',
    LF = 10,  // new line feed
    SEMI = ';',
    CR = 13,  // carriage return
    SPACE = 32,
    DOT = '.',
    EQ = '=',
    FUN 
};

// list of possible associativities (RIGHT is not needed "right" now)
enum ASSO { 
    LEFT, 
    NONE };

// Token Properties TOKEN -> PRIORITY(0=low), ASSOCIATIVITY
const map<TOKEN, tuple<int, ASSO>> tkProp = {
    {TOKEN::LIT, {1, ASSO::NONE}},
    {TOKEN::ADD, {2, ASSO::LEFT}},
    {TOKEN::SUB, {2, ASSO::LEFT}},
    {TOKEN::MUL, {3, ASSO::LEFT}},
    {TOKEN::DIV, {4, ASSO::LEFT}},
    {TOKEN::LPAR,{0, ASSO::NONE}},
    {TOKEN::RPAR,{0, ASSO::NONE}}};

class Token {
   public:
    virtual ~Token(){};
    virtual TOKEN getTk() = 0;
    virtual float v() const = 0;
    virtual void eval(vector<Token *> &stack) = 0;
    virtual void print(ostream &os) const = 0;
    virtual void RPN(vector<Token *> &output, vector<Token *> &stack) = 0;
    friend ostream &operator<<(ostream &os, const Token &t);
};

class Literal : public Token {
   private:
    TOKEN t;
    float num;

   public:
    ~Literal() {}
    Literal(float _num) : num(_num) {
        t = TOKEN::LIT;
    }
    TOKEN getTk() override { return t; }

    // valeur du Literal
    float v() const override { return num; }
    void eval(vector<Token *> &stack) override {
        stack.push_back(new Literal(num));
    }
    void print(ostream &os) const override { os << "Literal(" << v() << ")"; }
    void RPN(vector<Token *> &output, vector<Token *> &stack) override {
        output.push_back(this);
    }
};

class BinOp : public Token {
   private:
    TOKEN t;
    //if the token has a geater or equal precendence than
    inline bool gtEqPrec(Token* token) const {
        return (get<0>(tkProp.at(token->getTk())) >= get<0>(tkProp.at(t)));
    };
    inline bool isLpar(Token* token) const {
        return token->getTk() == TOKEN::LPAR;
    }
    float compute(float a, float b) {
        switch (t) {
            case TOKEN::ADD:
                return a + b;
            case TOKEN::SUB:
                return a - b;
            case TOKEN::MUL:
                return a * b;
            case TOKEN::DIV:
                return a / b;
        };
    }

   public:
    ~BinOp() {}
    float v() const override { return -1; }
    BinOp(TOKEN _t) : t(_t) {}
    TOKEN getTk() override { return t; }

    void eval(vector<Token *> &stack) override {
        if(stack.size() < 2){
            throw invalid_argument(
                    "Input string contains mismatched binary operators");
        }
        float b = stack.back()->v();
        delete stack.back();
        stack.pop_back();
        float a = stack.back()->v();
        delete stack.back();
        stack.pop_back();

        float res = compute(a, b);
        stack.push_back(new Literal(res));
    }
    void print(ostream &os) const override {
        os << "BinaryOp(" << (char)t << ")";
    }
    void RPN(vector<Token *> &output, vector<Token *> &stack) override {
        while (!stack.empty() && gtEqPrec(stack.back()) &&
               !isLpar(stack.back())) {
            output.push_back(move(stack.back()));
            stack.pop_back();
        }
        stack.push_back(move(this));
    }
};

class Par : public Token {
   private:
    TOKEN t;

   public:
    Par(TOKEN _t) : t(_t) {}
    ~Par() {}
    TOKEN getTk() override { return t; }
    float v() const override { return -1; }
    void eval(vector<Token *> &stack) override { stack.push_back(move(this)); }
    void print(ostream &os) const override {
        os << "(" << (t == TOKEN::LPAR ? "Left " : "Right ") << "Parenthesis)";
    }
    void RPN(vector<Token *> &output, vector<Token *> &stack) override {
        if (t == TOKEN::LPAR) {
            stack.push_back(move(this));
        } else if (t == TOKEN::RPAR) {
            if (stack.empty()) {
                throw invalid_argument(
                    "Input string contains mismatched parenthesis");
            }
            while (stack.back()->getTk() != TOKEN::LPAR) {
                if (stack.empty()) {
                    throw invalid_argument(
                        "Input string contains mismatched parenthesis");
                }
                output.push_back(move(stack.back()));
                stack.pop_back();
            }
            if (stack.back()->getTk() == TOKEN::LPAR) {
                delete stack.back();
                stack.pop_back();
            }
            delete this;
        }
    }
};

class Function : public Token {
   private:
    TOKEN t;
    vector<float> val; 
    std::function<float(vector<float>)> fun;

   public:
    ~Function() {}
    Function(std::function<float(vector<float>)> _fun, vector<float> value) : fun(_fun), val(value) {
        t = TOKEN::FUN;
    }
    TOKEN getTk() override { return t; }

    // valeur du Literal
    float v() const override { return -1; }
    void eval(vector<Token *> &stack) override {
        stack.push_back(new Literal(fun(val)));
    }
    void print(ostream &os) const override { os << "(Function)"; }
    void RPN(vector<Token *> &output, vector<Token *> &stack) override {
        output.push_back(this);
    }
};

#endif