#include <iostream>
#include "ArgParse.hpp"
//#include "Quine–McCluskey.hpp"
#include "Quine.hpp"

using namespace std;

int main(int argc, char **args){
    //Expression e;
    std::string file = string(args[1]);//"r3.txt";
    Expression exp = ParseFile(file);
    
    vector<string> mins = getPrimeImp(exp);
    cout << ".i " << exp.inLen << endl;
    cout << ".o " << exp.outLen << endl;
    cout << ".p " << mins.size() << endl;
    for (int i=0; i<mins.size(); i++){
        cout << mins[i] << " 1" << endl;
    }
    cout << ".e" << endl << endl;
    //vector<string> minBin = get_minterms(exp.inputs, exp.outputs);
    //vector< set<int>> funs = minimise(mins, minBin);
    //displayFunctions(funs, mins);
    return 0;
}