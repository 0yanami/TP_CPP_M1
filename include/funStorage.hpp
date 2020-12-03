#ifndef FUNSTORAGEH
#define FUNSTORAGEH

#include <functional>
#include <map>
#include <vector>
#include <cmath>

using namespace std;
//class for function storage
class FunStorage{

    //main functions memory
    //<name, < nbArguments, function >>
    map<string,pair<  int,function<float(vector<float>)>  >> mem;

    //curryfied functions memory
    //<name, <targetFunctionName, partialArguments>>
    map<string,pair< string,vector<float> >> curr_mem;

public:
    //add default functions at storage init
    FunStorage(){
        typedef vector<float> vf;
        this->addFun("cos",   1, [](vf v){ return cos(v[0]); });
        this->addFun("sin",   1, [](vf v){ return sin(v[0]); });
        this->addFun("tan",   1, [](vf v){ return tan(v[0]); });
        this->addFun("log",   1, [](vf v){ return log(v[0]); });
        this->addFun("exp",   1, [](vf v){ return exp(v[0]); });
        this->addFun("sqrt",  1, [](vf v){ return sqrt(v[0]); });
        this->addFun("pow",   2, [](vf v){ return pow(v[0],v[1]); });
        this->addFun("hypot", 2, [](vf v){ return hypot(v[0],v[1]);});
        this->addFun("lerp",  3, [](vf v){ return (v[1]*(1.0-v[0])) + (v[2]*v[0]); });
        this->addFun("polynome",-1,[](vf v){
        if(v.size()>2){
            float res = 0;
            float k = v.at(0);
            for(int i = v.size()-2; i != 0;i--){
                float fac = (k>0) ? pow(v.back(),k) : 1;
                res += v.at(i) * fac;
                k--;
            }
            return res;
        }
        return v.at(1);
        });
    };
    ~FunStorage(){};

    int getNbArgs(string _fName){
        //for general functions
        if(mem.find(_fName) != mem.end()){
            return get<0>(mem.at(_fName));
        }
        //for currified functions(get nbArgs of target function)
        return  getNbArgs(get<0>(curr_mem.at(_fName)));
    }
    //function exists in mem or curr_mem
    bool exists(string _fName){
        return (mem.find(_fName) != mem.end()) ||
               (curr_mem.find(_fName) != curr_mem.end());
    }

    bool isCurry(string _fName){
        return curr_mem.find(_fName) != curr_mem.end();
    }
    
    function<float(vector<float>)> getFun(string _fName){
        if(mem.find(_fName) != mem.end()){
            //fonction trouvé dans mem, on la retourne
            return get<1>(mem.at(_fName));
        } else {
            // sinon recherche de la fonction dans curr_mem
            return get<1>(mem.at(get<0>(curr_mem.at(_fName))));
        }
        
    }

    //get partial arguments of currefied function
    vector<float> getCurrArgs(string _fName){
        return get<1>(curr_mem.at(_fName));
    }
    //add traditional function
    void addFun(string _name, int _nbArgs, function<float(vector<float>)> _f){
        mem.emplace(pair{_name, pair{_nbArgs, _f}});
    }

    //add currefied function
    void addCurr(string _name, string _refName, vector<float> _partialArgs){
        curr_mem.emplace(pair{_name, pair{_refName,_partialArgs}});
    }

    //check if function accept number of args
    int funArgCheck(string _fName, int _nbArgs) {
        //return -1 for functions with variable number of args
        if(this->getNbArgs(_fName) == -1)return -1;
        //error if incorrect number of args
        if (this->getNbArgs(_fName) != _nbArgs) {
            string errMsg = "'" + _fName + "' expect "+to_string(this->getNbArgs(_fName)) + 
                            " args, " + to_string(_nbArgs) + " given.";
            throw ::invalid_argument(errMsg);
        }
    }
    //return number of missing arguments for currified functions
    int missingArgsCheck(string _fName, int _nbArgs) {
        //returns 1 for functions with variable number of args
        if(this->getNbArgs(_fName) == -1)return 1;
        //error if too many args given
        if (this->getNbArgs(_fName) < _nbArgs) {
            string errMsg = "'" + _fName + "' expect "+to_string(this->getNbArgs(_fName)) + 
                            " args, " + to_string(_nbArgs) + " given.";
            throw ::invalid_argument(errMsg);
        } else{
            return this->getNbArgs(_fName) - _nbArgs;
        }
    }    
};

#endif