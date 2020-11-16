#ifndef FUNSTORAGEH
#define FUNSTORAGEH

#include <functional>
#include <map>
#include <vector>
#include <cmath>

using namespace std;
//class for function storage
class FunStorage{
    //name, function
    map<string,pair<  int,function<float(vector<float>)>  >> mem;

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
        return get<0>(mem.at(_fName));
    }

    bool exists(string _fName){
        return mem.find(_fName) != mem.end();
    }

    function<float(vector<float>)> getFun(string _fName){
        return get<1>(mem.at(_fName));
    }

    void addFun(string name, int nbArgs, function<float(vector<float>)> _f){
        mem.emplace(pair{name, pair{nbArgs, _f}});
    }

    void funArgCheck(string _fName, int _nbArgs) {
        //no check for functions with variable number of args
        if(this->getNbArgs(_fName) == -1)return;
        if (this->getNbArgs(_fName) != _nbArgs) {
            string errMsg = "'" + _fName + "' expect "+to_string(this->getNbArgs(_fName)) + 
                            " args, " + to_string(_nbArgs) + " given.";
            throw ::invalid_argument(errMsg);
        }
    }
};

#endif