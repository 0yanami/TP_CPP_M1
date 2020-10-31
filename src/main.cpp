
//std headers
#include <iostream>
#include <string>


//project headers
#include "expression.hpp"
#include "program.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    Program p{cin};
    p.execute();
    /*
    string userInput;
    getline(cin ,userInput);
    
    Expression expr(userInput);
    
    expr.parse();
    cout << "input after parse: " <<expr.print() << endl;
    cout << "Eval: " << expr.eval() << endl;
    */
}