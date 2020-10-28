#include "expression.hpp"

Expression::Expression(string _str) : expr(_str){}

int Expression::eval(){
    return 0;
}

string Expression::print(){
    ostringstream out;
    auto tks = tokensFromString(expr);
    auto tks_parsed = parse(tks);
    for(auto& tok  :  tks_parsed){
        
        out << *tok;
    }
    cout << "fin du print : " << out.str() << endl;
    return out.str();
}


vector<unique_ptr<Token>> Expression::tokensFromString(const string& s){
    vector<unique_ptr<Token>> tokenList;
    for(auto i=s.begin(); i!= s.end();){
        //if char of string is a binop, add it
        
        if( binops.find(*i) != binops.end()){
            unique_ptr<BinOp> op(new BinOp(binops.at(*i)));
            tokenList.emplace_back(move(op));
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
            unique_ptr<Literal> lit_ptr(new Literal(stoi(lit)));
            tokenList.emplace_back(move(lit_ptr));
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

vector<unique_ptr<Token>> Expression::parse(vector<unique_ptr<Token>>& tokenList){
    
    vector<unique_ptr<Token>> output;
    vector<unique_ptr<Token>> stack;
    for(auto& token : tokenList){
        token->RPN(output,stack);
    }
    move(begin(stack), end(stack), back_inserter(output));
    return output;
}