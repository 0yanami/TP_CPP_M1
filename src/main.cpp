
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
}