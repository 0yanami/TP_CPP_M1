#include "expression.hpp"

Expression::Expression(string _str) : expr(_str){}

int Expression::eval(){
    return 0;
}

string Expression::print(){
    ostringstream out;
    auto tks = tokensFromString(expr);
    for(auto& tok  :  tks){
        out << *tok;
        delete tok;
    }
    return out.str();
}

string Expression::printWithParse(){
    ostringstream out;
    auto tks = tokensFromString(expr);
    auto tks_parsed = parse(tks);
    for(auto& tok  :  tks_parsed){
        out << *tok;
        delete tok;
    }
    return out.str();
}


vector<Token*> Expression::tokensFromString(const string& s){
    vector<Token*> tokenList;
    for(auto i=s.begin(); i!= s.end();){
        //if char of string is a binop, add it
        if( binops.find(*i) != binops.end()){
            tokenList.emplace_back(new BinOp(binops.at(*i)));
            i++;
        }
        //if char is a numerical value, iterate 
        else if (isdigit(*i)){
            string lit;
            //iterate over every next litterals for numbers
            while(i != s.end() && isdigit(*i)){
                lit.push_back(*i);
                i++;
            }
            tokenList.emplace_back(new Literal(stoi(lit)));
        }
        //skip spaces
        else if (isspace(*i)){
            i++;
        }
        //token is not recognized
        else {
            throw std::invalid_argument( "Input string contains unexpected token(s)");
        }
    }
    return tokenList;
}

vector<Token*> Expression::parse(vector<Token*>& tokenList){
    
    vector<Token*> output;
    vector<Token*> stack;
    for(auto& token : tokenList){
        token->RPN(output,stack);
    }
    move(begin(stack), end(stack), back_inserter(output));
    return output;
}