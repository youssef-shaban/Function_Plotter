#include <iostream>
#include "functiongenerator.h"
using namespace std;
int main() {


    cout<<FunctionGenerator::FCalc("(3*x/2+1)/(x+2)^2",3)<<endl;
}
