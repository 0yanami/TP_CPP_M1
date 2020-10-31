#include "expression.hpp"

map<char, TOKEN> Expression::binops = {
    {'-', SUB}, {'+', ADD}, {'/', DIV}, {'*', MUL}};

float Expression::eval(vector<Token *>& input) {
    vector<Token *> output;
    for (auto &token : input) {
        token->eval(output);
        
        
    }
    float res = output.back()->v();
    delete output.back();
    return res;
}

string Expression::print(vector<Token *> input) {
    ostringstream out;
    for (auto &tok : input) {
        out << *tok;
    }
    return out.str();
}

// generate a vector of tuple<list of tokens,"ends with SEMI"> for each line
// from input string
vector<tuple<vector<Token *>, bool>> Expression::tokensFromString(
    string& s, map<string, float>& var_memory) {
    vector<tuple<vector<Token *>, bool>> output;
    vector<Token *> lineBuffer;
    // iterate over each char of string
    for (auto i = s.begin(); i != s.end();) {
        int line_num = output.size() + 1;
        // if char of string is a binop, add it
        if (binops.find(*i) != binops.end()) {
            lineBuffer.emplace_back(new BinOp(binops.at(*i)));
            i++;
        }
        // if char is a numerical value, use the digitHandler method
        else if (isdigit(*i) || *i == TOKEN::DOT) {
            digitHandler(s, i, lineBuffer);
        }
        // if char is a parenthesis
        else if (*i == TOKEN::LPAR || *i == TOKEN::RPAR) {
            lineBuffer.emplace_back(new Par((TOKEN)*i));
            i++;
        }
        // parse function identifiers (starts with alpha char)
        else if (isalpha(*i)) {
            variableHandler(s, i, lineBuffer, var_memory, line_num);
        }
        // skip spaces
        else if (*i == TOKEN::SPACE) {
            i++;
        }
        // if semicolon found, add current line to output and clear lineBuffer
        else if (*i == TOKEN::SEMI) {
            output.emplace_back(tuple{lineBuffer, false});
            lineBuffer.clear();
            i++;
        }
        // if carriage return or line feed found
        else if (*i == TOKEN::CR || *i == TOKEN::LF) {
            //if lineBuffer is not empty, add it to output, else skip the char
            if (!lineBuffer.empty()) {
                output.emplace_back(tuple{lineBuffer, true});
                lineBuffer.clear();
                i++;
            } else {
                i++;
            }
        }
        // token is not recognized
        else {
            unexpectedHandler(i,line_num);
        }
    }
    // add the last line (if no CR at the end of input string)
    if (!lineBuffer.empty()) {
        output.emplace_back(tuple{lineBuffer, true});
    }
    return output;
}

void Expression::variableHandler(string& s, string::iterator& i, vector<Token *>& lineBuffer, map<string, float>& var_memory,int line_num) {
    string id = "";
    id.push_back(*i);
    i++;
    // variable id begins with either alpha, digit or underscore
    while (isalpha(*i) || isdigit(*i) || *i == '_') {
        id.push_back(*i);
        i++;
    }
    // end of id reading
    while (*i == TOKEN::SPACE) {
        i++;
    }
    // if assignation
    if (*i == TOKEN::EQ) {
        i++;
        // evaluate the expression after '=' until linebreak or semi
        string subeval = "";

        while (i != s.end() && *i != TOKEN::SEMI && *i != TOKEN::CR) {
            if (*i != TOKEN::SPACE) subeval.push_back(*i);
            i++;
        }
        //if expression after '=' is empty
        if (subeval.size() == 0) {
            throw invalid_argument("expected expression after variable " + id +
                                   " = ... [line " + to_string(line_num) + "]");
        }
        //evaluate the expression
        auto subTks = tokensFromString(subeval, var_memory)[0];
        auto parsedSubTks = parse(get<0>(subTks));
        float value = eval(parsedSubTks);
        //clean memory
        for(auto& tk : parsedSubTks){
            delete tk;
        }
        //if the id is not in memory add the pair id/value
        if (var_memory.find(id) == var_memory.end()) {
              var_memory.insert(make_pair(id, value));
        }
        //is the id is in memory, modify the value of id
        else{
            var_memory.at(id) = value;
        }
    }
    // no assignation, expecting a call
    else {
        if (var_memory.find(id) != var_memory.end()) {
            //a call adds the value of the variable as a litteral
            lineBuffer.emplace_back(new Literal(var_memory.at(id)));
        } else {
            throw invalid_argument("variable " + id +
                                   " referenced before assignment");
        }
    }
};

void Expression::digitHandler(string& s,string::iterator& i, vector<Token *>& lineBuffer){
    string lit;
            // iterate over every next literals or '.' for numbers
            while (i != s.end() && (isdigit(*i) || *i == TOKEN::DOT)) {
                lit.push_back(*i);
                i++;
            }
            lineBuffer.emplace_back(new Literal(stof(lit)));
};

//handle unexpected token/char
void Expression::unexpectedHandler(string::iterator& i, int line_num){
    string s = "[line"+to_string(line_num)+"]Input string contains unexpected token(s): '";
            s.append(&*i);
            s.append("' (ASCII code " + to_string((int)*i) + ")");
            throw invalid_argument(s);
};

// transform the tokenList to rpn representation
vector<Token *> Expression::parse(vector<Token *> input) {
    vector<Token *> output;
    vector<Token *> stack;
    for (auto &token : input) {
        token->RPN(output, stack);
    }
    reverse(begin(stack), end(stack));
    // deletes redundant parenthesis stuck in the stack
    copy_if(make_move_iterator(stack.begin()), make_move_iterator(stack.end()),
            back_inserter(output), [](Token *t) {
                if((t->getTk() != TOKEN::LPAR) && (t->getTk() != TOKEN::RPAR)){
                    return true;
                }
                delete t;
                return false;
            });
    return output;
}