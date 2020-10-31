#ifndef EXPRESSIONH
#define EXPRESSIONH

#include <algorithm>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>

#include "token.hpp"

using namespace std;

/*
test = 35/(32-7.443);
sauce = 33.28*(11-test);
test = sauce / 1.11;
test
*/
class Expression {
   private:
    static map<char, TOKEN> binops;
    static void variableHandler(string& s, string::iterator& i,
                                vector<Token*>& lineBuffer,
                                map<string, float>& var_memory, int line_num);

    static void digitHandler(   string& s, string::iterator& i,
                                vector<Token*>& lineBuffer);

    static void binOpHandler();
    static void unexpectedHandler(string::iterator& i, int line_num);

   public:
    static vector<tuple<vector<Token*>, bool>> tokensFromString(
        string& s, map<string, float>& mem);

    Expression(string _str);
    static float eval(vector<Token*> input);
    static string print(vector<Token*> input);
    static vector<Token*> parse(vector<Token*> input);
};

#endif