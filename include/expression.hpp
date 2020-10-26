#ifndef EXPRESSIONH
#define EXPRESSIONH

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include "token.hpp"


using namespace std;

class Expression {
public:
    Expression(string _str);
    int eval();
    void print();
private:
    const vector<char> binOps{'+','-','/','*'} ;
    vector<Token*> tokensFromString(const string& s);
    void printToks(vector<Token*> tokenList);
    string expr;
};


#endif