#include "functiongenerator.h"
#include <stack>
#include <queue>
#include <sstream>
#include <cmath>
FunctionGenerator::FunctionGenerator()
{

}

string FunctionGenerator::infixToPostfix(const string& infix) {
    const std::string ops = "-+/*^";
    std::stringstream ss;
    std::stack<int> s;
    symbolChecker(infix);
    std::stringstream input(infix);
    std::string token;
    int closedBracket=0;
    while (std::getline(input, token, ' ')) {
        if (token.empty()) {
            continue;
        }

        char c = token[0];
        size_t idx = ops.find(c);

        // check for operator
        if (idx != std::string::npos) {
            while (!s.empty()) {
                int prec2 = s.top() / 2;
                int prec1 = idx / 2;
                if (prec2 > prec1 || (prec2 == prec1 && c != '^')) {
                    ss << ops[s.top()] << ' ';
                    s.pop();
                } else break;
            }
            s.push(idx);
        } else if (c == '(') {
            closedBracket++;
            s.push(-2); // -2 stands for '('
        } else if (c == ')') {
            closedBracket--;
            // until '(' on stack, pop operators.
            while (s.top() != -2) {
                ss << ops[s.top()] << ' ';
                s.pop();
                if(s.empty()){
                    throw std::runtime_error("You are closing a bracket without opening it.");
                }
            }
            s.pop();
        } else {
            ss << token << ' ';
        }
    }
    if(closedBracket!=0)
        throw std::runtime_error("Please close opened brackets.");
    while (!s.empty()) {
        ss << ops[s.top()] << ' ';
        s.pop();
    }

    return ss.str();
}

double FunctionGenerator::postfixToNum(string postfix)
{
    stack<int> stack;
    const string ops = "-+/*^";


    stringstream lst;
    stringstream input(postfix);
    string token;
    while (std::getline(input, token, ' ')) {
        if (token.empty()) {
            continue;
        }
        char c = token[0];
        size_t idx = ops.find(c);
        if(idx!=-1&& token.length()==1){
            double val1= 0;
            double val2= 0;
            if(stack.size()==0){
               throw std::runtime_error("please you a numbers or x in the equation");
            }else if(stack.size()==1){
                if(c=='-'){ val1= stack.top(); stack.pop();}

                else throw std::runtime_error("you can't use ** or // or any two symbols");
            }else{
                val1= stack.top(); stack.pop();
                val2= stack.top(); stack.pop();
            }

            if(token=="+")
                stack.push(val2+val1);
            else if(token=="-")
                stack.push(val2-val1);
            else if(token=="*")
                stack.push(val2*val1);
            else if(token=="/")
                stack.push(val2/val1);
            else if(token=="^")
                stack.push(pow(val2,val1));}
        else{
            double num= stod(token);

            stack.push(num);
       }
    }

    return stack.top();
}

void FunctionGenerator::symbolChecker(string exp)
{
    for(int i =0;i<exp.length();i++){
        char letter = exp[i];
        if((letter>=40&&letter<=57)||letter==120||letter==32||letter==94){
            continue;
        }else throw std::runtime_error("ONLY USE numbers, x, ^*-+/()");
    }
    return;
}


double FunctionGenerator::FCalc(string exp, double num)
{
    exp=infixToPostfix(spacer(exp));
    string str= Replacer(exp,to_string(num),"x");
    return postfixToNum(str);
}

string FunctionGenerator::spacer(string exp)
{
    const string ops = "-+/*^()";
    string s1="";
    for(auto c:exp) {
        size_t idx = ops.find(c);
        if (idx != -1){
            s1=s1+" "+c+" ";
        }else{
            s1+=c;
        }
    }
    return s1+" ";
}

string FunctionGenerator::Replacer(string str, const string sub, const string mod)
{
    int index;
    string tmp(str);
    while((index = str.find(mod)) != -1) {
        str=str.substr(0,index)+sub+str.substr(index+mod.size());
    }
    return str;
}
