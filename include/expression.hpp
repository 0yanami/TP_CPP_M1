#ifndef EXPRESSIONH
#define EXPRESSIONH

#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include "token.hpp"


using namespace std;

class Expression {
public:
    Expression(string _str);
    ~Expression();
    float eval();
    string print();
    void parse();
private:
    const map<char, TOKEN> binops
    {
        { '-', SUB },
        { '+', ADD },
        { '/', DIV },
        { '*', MUL }
    };
    void tokensFromString();
    
    string input_expr;
    //La suite de tokens que l'on manipule
    vector<Token*> tokenList;
};

#endif