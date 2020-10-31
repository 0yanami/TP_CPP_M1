#ifndef PROGRAMH
#define PROGRAMH


#include <string>
#include <vector>
#include <iostream>

#include "token.hpp"
#include "expression.hpp"

using namespace std;

class Program{
private:
    string prog_input;
    vector<tuple<vector<Token*>,bool>> program;
public:
    Program(istream& _s){
        string str_s(istreambuf_iterator<char>(_s), {});
        prog_input = str_s;
        /*
        for (auto i = prog_input.begin(); i != prog_input.end();i++){
            cout << "reading: " << (int)*i << endl;
        }
        cout << "finished" << endl;
        */
        
    }
    void execute();
};

#endif