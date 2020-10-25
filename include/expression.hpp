#ifndef EXPRESSIONH
#define EXPRESSIONH

#include<string>
#include <vector>
#include "token.hpp"
using namespace std;

class Expression {
public:
    Expression(string _str);
    int eval();
    void print();
private:
    vector<Token*> tokensFromString(const string& s, char delim);
    string expr;
};


#endif