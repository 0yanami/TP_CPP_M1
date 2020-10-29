
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
    cout << "input before parse: " <<expr.print() << endl;
    expr.parse();
    cout << "input after parse: " <<expr.print() << endl;
    cout << "Eval: " << expr.eval() << endl;
}
/*
Numeral(17)Numeral(24)Numeral(4)Operateur(/)Numeral(3)Operateur(*)Numeral(2)Operateur(-)Operateur(+)

17 24 4 
/
17 6
17 6 3
*
17 18
17 18 2
-
17 16
*/