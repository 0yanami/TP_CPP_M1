
//std headers
#include <iostream>
#include <string>


//project headers
#include "expression.hpp"

using namespace std;

int main (int argc, char *argv[]) {
    string userInput;
    while(true){
        cin >> userInput;
        cout << "Output: " << endl;
        Expression expr(userInput);
        cout << expr.print();
    }
}