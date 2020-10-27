#ifndef EXPRESSIONH
#define EXPRESSIONH

#include <string>
#include <vector>
#include <algorithm>
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
    const vector<char> binOps{'+','-','/','*'} ;
    vector<Token*> tokensFromString(const string& s);
    string printToks(vector<Token*> tokenList);
    string expr;
};


#endif