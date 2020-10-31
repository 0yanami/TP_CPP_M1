#include "token.hpp"


ostream& operator<<(ostream& os, const Token& t){
        t.print(os);
	    return os;
}