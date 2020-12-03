#include "expression.hpp"

map<char, TOKEN> Expression::binops = {
    {'-', SUB}, {'+', ADD}, {'/', DIV}, {'*', MUL}};

float Expression::eval(vector<Token *> &input) {
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
vector<tuple<vector<Token *>, bool>> Expression::tokensFromString() {

    vector<tuple<vector<Token *>, bool>> output;
    vector<Token *> lineBuffer;
    // iterate over each char of string
    for (auto i = s.begin(); i != s.end();) {
        int line_num = output.size() + 1;
        // if char is a numerical value, use the digitHandler method
        if (isdigit(*i) || *i == TOKEN::DOT) {
            digitHandler(s, i, lineBuffer);
        }
        // negative values at start ie. -0.25 or -.25
        else if (i == s.begin() && *i == TOKEN::SUB && isdigit(*(i + 1)) ||
                 *(i + 1) == TOKEN::DOT) {
            digitHandler(s, i, lineBuffer);
        }
        // if char of string is a binop, add it
        else if (binops.find(*i) != binops.end()) {
            lineBuffer.emplace_back(new BinOp(binops.at(*i)));
            i++;
        }
        // if char is a parenthesis
        else if (*i == TOKEN::LPAR || *i == TOKEN::RPAR) {
            lineBuffer.emplace_back(new Par((TOKEN)*i));
            i++;
        }
        // parse id for function or variable handling (starts with alpha char)
        else if (isalpha(*i)) {
            string id = "";
            id.push_back(*i);
            i++;
            // variable id begins with either alpha, digit or underscore
            while (isalpha(*i) || isdigit(*i) || *i == '_') {
                id.push_back(*i);
                i++;
            }
            // skip end of id reading
            while (*i == TOKEN::SPACE) {
                i++;
            }
            if(*i == TOKEN::LPAR){
                funHandler(id, i, lineBuffer, line_num);
            }
            else{
                varHandler(id, i, lineBuffer, line_num);
            }
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
            // if lineBuffer is not empty, add it to output, else skip the char
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
            unexpectedHandler(i, line_num);
        }
    }
    // add the last line (if no CR at the end of input string)
    if (!lineBuffer.empty()) {
        output.emplace_back(tuple{lineBuffer, true});
    }
    return output;
}




void Expression::funHandler(string &id, string::iterator &i, vector<Token *> &lineBuffer, int line_num) {
    stringstream args;
    //reading arguments
    i++;
    while(i == s.end() || *i != TOKEN::RPAR ){
        args << *i;
        i++;
    }

    vector<float> split_args;
    string str;
    while (getline(args, str, ',')) {
        split_args.push_back(stof(str));
    }

    i++;
    //si on trouve la fonction dans la mémoire fun_mem, on ajoute le token au linebuffer
    cout << "exists: " << id << endl;
    if(fun_mem.exists(id)){
        //un function is curryfied, add it's missing args
        if(fun_mem.isCurry(id)){
            vector<float> currArgs = fun_mem.getCurrArgs(id);
            currArgs.insert(currArgs.end(), split_args.begin(),split_args.end());
            split_args = currArgs;
        }
        for(float i : split_args){
            cout << i << endl;
        }
        fun_mem.funArgCheck(id,split_args.size());
        lineBuffer.emplace_back(new Function(fun_mem.getFun(id), split_args));
    } else {
        throw invalid_argument("unknown reference to function '" + id +
                                   "' [line " + to_string(line_num) + "]");
    }
};

//for currified functions handling, returns true if curryfield functions was handled
bool Expression::handleCurryfied(string &id, string::iterator &i){
    int dec = 0; //TODO: enlever a avec un iterator temp plus tard
    while(*i == TOKEN::SPACE){
        i++;
        dec++;
    }
    if(isalpha(*i)){
        string fName = ""; // name of new currefied function
        while(isalpha(*i)){
            fName.push_back(*i);
            i++;
            dec++;
        }
        cout << fName<<endl;
        //if function is read and function exists
        if(*i == TOKEN::LPAR && fun_mem.exists(fName)){
            stringstream args;
            //read arguments of function
            i++;
            dec++;
            while(i == s.end() || *i != TOKEN::RPAR ){
                args << *i;
                i++;
                dec++;
            }
            i++;
            dec++;
            vector<float> split_args;
            string str;
            while (getline(args, str, ',')) {
                split_args.push_back(stof(str));
            }
            int nbArgsMissing = fun_mem.missingArgsCheck(fName,split_args.size());
            cout << nbArgsMissing << endl;
            if( nbArgsMissing > 0){
                //add function 'id' with reference to 'fName' with args 'split_args'
                fun_mem.addCurr(id,fName,split_args);
                return true;
            } else {
                // no missing args - >normal function
                // revert iterator and discard
                i -= dec;
                return false;
            }
        } else {
            //not a function, discard it.
            i -= dec;
            return false;
        }
    }
    i -= dec;
    return false;
}

void Expression::varHandler(string &id, string::iterator &i, vector<Token *> &lineBuffer, int line_num) {
    if(*i == TOKEN::EQ){
        i++;

        if(handleCurryfied(id, i)){
            return;
        }
        // evaluate the expression after '=' until linebreak or semi
        string subeval = "";

        while (*i != TOKEN::SEMI && *i != TOKEN::CR) {
            if (*i != TOKEN::SPACE) subeval.push_back(*i);
            i++;
        }
        // if expression after '=' is empty
        if (subeval.size() == 0) {
            throw invalid_argument("expected expression after variable " + id +
                                   " = ... [line " + to_string(line_num) + "]");
        }
        // evaluate the expression
        Expression e{subeval,var_mem,fun_mem};
        auto subTks = e.tokensFromString()[0];
        auto parsedSubTks = parse(get<0>(subTks));
        float value = eval(parsedSubTks);
        // clean memory
        for (auto &tk : parsedSubTks) {
            delete tk;
        }
        // if the id is not in memory add the pair id/value
        if (var_mem.find(id) == var_mem.end()) {
            var_mem.insert(make_pair(id, value));
        }
        // else, modify the value of id
        else {
            var_mem.at(id) = value;
        }
    }
    // no assignation, expecting a call
    else {
        if (var_mem.find(id) != var_mem.end()) {
            // a call adds the value of the variable as a litteral
            lineBuffer.emplace_back(new Literal(var_mem.at(id)));
        } else {
            throw invalid_argument("variable " + id +
                                   " referenced before assignment");
        }
    }
    
};



void Expression::digitHandler(string &s, string::iterator &i,
                              vector<Token *> &lineBuffer) {
    string lit;
    bool isNeg = false;
    if (*i == TOKEN::SUB) {
        isNeg = true;
        i++;
    }
    // iterate over every next literals or '.' for numbers
    while (i != s.end() && (isdigit(*i) || *i == TOKEN::DOT)) {
        lit.push_back(*i);
        i++;
    }
    float val = stof(lit);
    lineBuffer.emplace_back(new Literal(isNeg ? -val : val));
};

// handle unexpected token/char
void Expression::unexpectedHandler(string::iterator &i, int line_num) {
    string s = "[line" + to_string(line_num) +
               "]Input string contains unexpected token(s): '";
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
    copy_if(
        make_move_iterator(stack.begin()), make_move_iterator(stack.end()),
        back_inserter(output), [](Token *t) {
            if ((t->getTk() != TOKEN::LPAR) && (t->getTk() != TOKEN::RPAR)) {
                return true;
            }
            delete t;
            return false;
        });
    return output;
}