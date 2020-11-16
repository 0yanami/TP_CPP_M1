#ifndef PROGRAMH
#define PROGRAMH


#include <string>
#include <vector>
#include <iostream>

#include "token.hpp"
#include "expression.hpp"
#include "funStorage.hpp"

using namespace std;

class Program{
private:
    string prog_input;
    vector<tuple<vector<Token*>,bool>> program;
public:
    Program(istream& _s){
        string str_s(istreambuf_iterator<char>(_s), {});
        prog_input = str_s;
    }
    //constructor for googletest tests
    Program(string _s): prog_input(_s){};

    void execute();

    //method returns a string for googletest tests
    string executeString();
};

#endif