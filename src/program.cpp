#include "program.hpp"


void Program::execute(){
    cout << endl <<"Input size = " << prog_input.size()  << endl;
    map<string, float> memory {};
    program = Expression::tokensFromString(prog_input,memory);
    for(auto line : program){
        vector<Token *> line_parsed = Expression::parse(get<0>(line));
        //cout << Expression::print(line_parsed) << endl;
        if(get<1>(line)){
            cout << Expression::eval(line_parsed) << endl;
        }

    }
}