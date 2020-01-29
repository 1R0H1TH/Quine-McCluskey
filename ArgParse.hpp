#ifndef __ARGPARSEINC__
#define __ARGPARSEINC__

#include <stdio.h>
#include <fstream>
#include <vector>

//using namespace std;

typedef unsigned char byte;

typedef struct {
    int inLen;
    int outLen;
    int expLen;
    std::vector<std::string> inputs;
    std::vector<std::string> outputs;
} Expression;//, *pExpression;

void skipWhitespace(std::ifstream &in){
    while (true){
        char c;
        if (!in.read(&c, 1).eof()) {
            if (!isspace(c)){
                if (c == '#'){
                    std::string line;
                    std::getline(in, line);
                } else { 
                    in.seekg(-1, std::ios::cur);
                    break;
                }
            }
        } else break;
    }
}
/*pExpression ParseFile(string str){
    pExpression exp = new Expression();
    fstream f(str, ios::in);
    
    int a=0;
    char c;
    bool inp = true;
    while (f.peek() >= 0){
        skipWhitespace(f);
        f.read(&c, 1);
        if (c == '.'){
            f.read(&c, 1);
            if (c == 'i'){
                skipWhitespace(f);
                f >> exp->inLen;
            } else if (c == 'o'){
                skipWhitespace(f);
                f >> exp->outLen;
            }
        } else {
            if (inp){
                f.read(&c, 1);
                while (c == '0' || c == '1'){

                }
            }
        }
    }
    f.close();
    
    
    return exp;
}*/
Expression ParseFile(std::string str){
    Expression exp;
    std::ifstream f(str, std::ios::in);
    char c;
    skipWhitespace(f);
    f.read(&c, 1); f.read(&c, 1); f.read(&c, 1);// read .i 
    f >> exp.inLen;
    skipWhitespace(f);
    f.read(&c, 1); f.read(&c, 1); f.read(&c, 1);// read .o
    f >> exp.outLen;
    //f.read(&c, 1);
    while (f.peek() >= 0)
    {
        skipWhitespace(f);
        std::string tmp0, tmp1; int bit;
        for (int i=0; i < exp.inLen; i++){
            f.read(&c, 1); bit = c == '1';
            tmp0 += c;
        }
        exp.inputs.push_back(tmp0);
        skipWhitespace(f);
        for (int i=0; i < exp.outLen; i++){
            f.read(&c, 1); bit = c == '1';
            tmp1 += c;
        }
        exp.outputs.push_back(tmp1);
        skipWhitespace(f);
    }
    
    return exp;
}
void printExp(Expression e){
    int len = e.inputs.size(), inlen = e.inputs[0].size(), outlen = e.outputs[0].size();
    for (int i=0; i < len; i++){
        std::cout << e.inputs[i] << " " << e.outputs[i] << std::endl;
    }
}
#endif