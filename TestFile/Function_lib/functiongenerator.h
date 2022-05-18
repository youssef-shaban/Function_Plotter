#ifndef FUNCTIONGENERATOR_H
#define FUNCTIONGENERATOR_H
#include <string>
using namespace std;
class FunctionGenerator
{
public:
    FunctionGenerator();
    static double FCalc(string exp, double num);


private:
    static string spacer(string exp);
    static string Replacer(string str, const string sub, const string mod);
    static string infixToPostfix(const string& infix);
    static double postfixToNum(string postfix);
    static void symbolChecker(string exp);
};

#endif // FUNCTIONGENERATOR_H
