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
#include <functional>

#include "token.hpp"
#include "funStorage.hpp"

using namespace std;

class Expression {
   private:
    string s;
    static map<char, TOKEN> binops;
    map<string, float> var_mem;
    FunStorage fun_mem;

    void varHandler(string& id, string::iterator& i,
                                vector<Token*>& lineBuffer, int line_num);

    void funHandler(string& id, string::iterator& i,
                                vector<Token*>& lineBuffer, int line_num);

    void digitHandler(   string& s, string::iterator& i,
                                vector<Token*>& lineBuffer);

    void binOpHandler();
    void unexpectedHandler(string::iterator& i, int line_num);

   public:
    Expression(string _str,
        map<string, float>& _var_mem,
        FunStorage& _fun_mem): s(_str), var_mem(_var_mem), fun_mem(_fun_mem){};
    Expression(string _str): s(_str),
                            var_mem(map<string, float>{}),
                            fun_mem(FunStorage{}){};
    
    vector<tuple<vector<Token*>, bool>> tokensFromString();
    //TODO: mettre ça dans une classe statique parser?
    static float eval(vector<Token*>& input);
    static string print(vector<Token*> input);
    static vector<Token*> parse(vector<Token*> input);
};

#endif