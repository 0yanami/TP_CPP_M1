#include "expression.hpp"

Expression::Expression(string _str) : expr(_str){}

int Expression::eval(){
    
}

string Expression::print(){
    vector<Token*> tokenList = tokensFromString(expr);
    return printToks(tokenList);
}

string Expression::printToks(vector<Token*> tokenList){
    ostringstream out;
        for(Token* tok  : tokenList){
        out << *tok;
    }
    return out.str();
}

vector<Token*> Expression::tokensFromString(const string& s){
    vector<Token*> tokenList;
    for(auto i=s.begin(); i!= s.end();){
        //if char of string is a binop, add it
        if(find(binOps.begin(),binOps.end(),*i) != binOps.end()){
            tokenList.push_back(new BinOp(*i));
            i++;
        }
        //if char is a numerical value, iterate 
        else if (isdigit(*i)){
            string lit;
            while(i != s.end() && isdigit(*i)){
                lit.push_back(*i);
                i++;
            }
            tokenList.push_back(new Literal(stoi(lit)));
        }
        else {
            throw std::invalid_argument( "Input string contains unexpected tokens" );
        }
    }
    return tokenList;
}