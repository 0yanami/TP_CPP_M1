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
    int eval();
    string print();
private:
    const map<char, TOKEN> binops
    {
        { '-', SUB },
        { '+', ADD },
        { '/', DIV },
        { '*', MUL },
        { ')', RPAR },
        { '(', LPAR }
    };
    vector<Token*> tokensFromString(const string& s);
    vector<Token*> parse(vector<Token*>& tokenList);
    string expr;
    
};


#endif