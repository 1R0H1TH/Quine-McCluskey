#include <algorithm> 
#include <chrono> 
#include <iostream> 
#include <math.h>
#include "ArgParse.hpp"
#include "Quine.hpp"
using namespace std; 
using namespace std::chrono;

int randBit(){
    return rand() % 2;
}
Expression getRandomExp(int inLen, int outLen){
    Expression ret;
    ret.inLen = inLen;
    ret.outLen = outLen;
    unsigned long long max = (unsigned long long)powf64(2, inLen);
    for (unsigned long long i=0; i<max; i++){
        ret.inputs.push_back(intToBinString(inLen, i));
        ret.outputs.push_back(to_string(randBit()));
    }
    return ret;
}
void saveExp(Expression e, string name){
    ofstream fout(name);
    //fout.open(name);
    fout << ".i " << e.inLen << endl;
    fout << ".o " << e.outLen << endl;
    for (int i=0; i < e.inputs.size(); i++){
        fout << e.inputs[i] << " " << e.outputs[i] << endl;
    }
    fout.close();
}
double timeOf(string cmd, int c){
    double ret=0;
    cmd += " >>/dev/null 2>>/dev/null";
    for (int i=0; i<c; i++){
        auto start = high_resolution_clock::now();
        int r = system(cmd.c_str());
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        ret += duration.count();
    }
    
    return ret/(double)c/1e+6;
}

int main(){
    srand(time(0));
    /*cout << timeOf("./Main r3.txt", 1) << endl;
    cout << timeOf("espresso r3.txt", 1) << endl;
    Expression exp = getRandomExp(2, 1);
    saveExp(exp, "r4.txt");
    cout << randBit() << endl;*/
    ofstream f("eval_result.txt");
    for (int i=15; i<16; i++){
        Expression exp = getRandomExp(i, 1);
        saveExp(exp, "eval_test.txt");
        double tesp = timeOf("espresso eval_test.txt", 5);
        double tqui = timeOf("./Main eval_test.txt", 5);
        f << tesp << " " << tqui << endl;
    }
    f.close();
}