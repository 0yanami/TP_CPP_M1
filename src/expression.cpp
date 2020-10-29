#include "expression.hpp"

Expression::Expression(string _str) : input_expr(_str){
    tokensFromString();
}

Expression::~Expression(){
    for(auto& tok  :  tokenList){
        delete tok;
    }
};

float Expression::eval(){
    vector<Token*> output;
    for(auto& token : tokenList){
        token->eval(output);
    }
    auto res = output.back()->v();
    delete output.back();
    return res;
}

string Expression::print(){
    ostringstream out;
    for(auto& tok  :  tokenList){
        out << *tok;
    }
    return out.str();
}

//generate a token list form input string
void Expression::tokensFromString(){
    //iterate over each char of string
    for(auto i = input_expr.begin(); i!= input_expr.end();){
        //if char of string is a binop, add it
        if( binops.find(*i) != binops.end()){
            tokenList.emplace_back(new BinOp(binops.at(*i)));
            i++;
        }
        //if char is a numerical value, iterate 
        else if (isdigit(*i)|| *i == '.'){
            string lit;
            //iterate over every next litterals for numbers
            while(i != input_expr.end() && (isdigit(*i)|| *i == '.')){
                lit.push_back(*i);
                i++;
            }
            tokenList.emplace_back(new Literal(stof(lit)));
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
}

//transform the tokenList to rpn representation
void Expression::parse(){
    vector<Token*> output;
    vector<Token*> stack;
    for(auto& token : tokenList){
        token->RPN(output,stack);
    }
    reverse(begin(stack), end(stack));
    move(begin(stack), end(stack), back_inserter(output));
    tokenList = output;
}