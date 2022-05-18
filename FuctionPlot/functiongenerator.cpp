#include "functiongenerator.h"
#include <QStack>
#include <QQueue>
#include <QString>
#include <QtMath>
#include <QDebug>

FunctionGenerator::FunctionGenerator()
{

}

QString FunctionGenerator::infixToPostfix(const QString &infix)
{
    const QString ops = "-+/*^";
    symbolChecker(infix);
    QQueue<QString> queue;
    QStack<int> s;
    QString token;
    QStringList lst= infix.split(" ");
    int closedBracket=0;
    for(auto token:lst) {

        if (token=="") {

            continue;
        }

        QChar c = token[0];
        qsizetype idx = ops.indexOf(c);

        // check for operator
        if (idx != -1&&token.length()==1) {
            while (!s.empty()) {
                int prec2 = s.top() / 2;
                int prec1 = idx / 2;
                if (prec2 > prec1 || (prec2 == prec1 && c != '^')) {
                    QString op(1,ops[s.top()]);
                    queue.enqueue(op);
                    queue.enqueue(" ");
                    s.pop();
                } else break;
            }
            s.push(idx);
        } else if (c == '(') {
            closedBracket++;
            s.push(-2); // -2 stands for '('
        } else if (c == ')') {
            // until '(' on stack, pop operators.
            closedBracket--;
            while (s.top() != -2) {
                QString op(1,ops[s.top()]);
                queue.enqueue(op);
                queue.enqueue(" ");
                s.pop();
                if(s.empty()){
                    throw std::runtime_error("You are closing a bracket without opening it.");
                }
            }
            s.pop();
        } else {
            queue.enqueue(token);
            queue.enqueue(" ");
        }

    }
    if(closedBracket!=0)
        throw std::runtime_error("Please close opened brackets.");
    while (!s.empty()) {
        QString op(1,ops[s.top()]);
        queue.enqueue(op);
        queue.enqueue(" ");
        s.pop();
    }
    QString output="";
    while(!queue.empty()){
       output+= queue.dequeue();
    }
    return output;
}

qreal FunctionGenerator::postfixToNum(QString postfix)
{
    QStack<qreal> stack;
    const QString ops = "-+/*^";


    QStringList lst= postfix.split(" ");
    lst.removeLast();
    for(auto s:lst) {
        QChar c = s[0];
        qsizetype idx = ops.indexOf(c);
        if(idx!=-1&& s.length()==1){
            qreal val1= 0;
            qreal val2= 0;
            if(stack.size()==0){
               throw std::runtime_error("please you a numbers or x in the equation");
            }else if(stack.size()==1){
                if(c=='-') val1= stack.pop();
                else throw std::runtime_error("you can't use ** or // or any two symbols");
            }else{
                val1= stack.pop();
                val2= stack.pop();
            }

            if(s=="+")
                stack.push(val2+val1);
            else if(s=="-")
                stack.push(val2-val1);
            else if(s=="*")
                stack.push(val2*val1);
            else if(s=="/")
                stack.push(val2/val1);
            else if(s=="^")
                stack.push(qPow(val2,val1));}
        else{
            qreal num= s.toFloat();

            stack.push(num);
       }
    }

    return stack.top();
}

void FunctionGenerator::symbolChecker(QString exp)
{
    for(int i =0;i<exp.length();i++){
        QChar letter = exp[i];
        if((letter>=40&&letter<=57)||letter==120||letter==32){
            return;
        }else throw std::runtime_error("ONLY USE numbers, x, ^*-+/()");
    }
}


qreal FunctionGenerator::FCalc(QString exp, qreal num)
{
    exp=infixToPostfix(spacer(exp));
    QString str= Replacer(exp,QString::number(num),"x");
    return postfixToNum(str);
}

QString FunctionGenerator::spacer(QString exp)
{
    const QString ops = "-+/*^()";
    QString s1="";
    for(auto c:exp) {
        qsizetype idx = ops.indexOf(c);
        if (idx != -1){
            s1=s1+" "+c+" ";
        }else{
            s1+=c;
        }
    }
    return s1+" ";
}

QString FunctionGenerator::Replacer(QString str, const QString sub, const QString mod)
{
    int index;
    QString tmp(str);
    while((index = str.indexOf(mod)) != -1) {
        str=str.mid(0,index)+sub+str.mid(index+mod.size());
    }
    return str;
}
