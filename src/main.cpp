
//std headers
#include <iostream>
#include <string>

//project headers
#include "expression.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    string userInput = "3+5";
    //getline(cin ,userInput);
    cout << "Output: (size=" << userInput.size() << ")" << endl;
    Expression expr(userInput);
    cout << "Input ["<<userInput <<"] after parsing: "<<expr.print() << endl;
    cout << "fin prog" << endl;
}