
//std headers
#include <iostream>
#include <string>

//project headers
#include "expression.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    string userInput;
    getline(cin ,userInput);
    cout << "Output: (size=" << userInput.size() << ")" << endl;
    Expression expr(userInput);
    cout << expr.print() << endl;
}