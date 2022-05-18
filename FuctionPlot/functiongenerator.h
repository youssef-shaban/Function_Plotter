#ifndef FUNCTIONGENERATOR_H
#define FUNCTIONGENERATOR_H
#include <QString>

class FunctionGenerator
{
public:
    FunctionGenerator();
    static qreal FCalc(QString exp, qreal num);


private:
    static QString spacer(QString exp);
    static QString Replacer(QString str, const QString sub, const QString mod);
    static QString infixToPostfix(const QString& infix);
    static qreal postfixToNum(QString postfix);
    static void symbolChecker(QString exp);
};

#endif // FUNCTIONGENERATOR_H
