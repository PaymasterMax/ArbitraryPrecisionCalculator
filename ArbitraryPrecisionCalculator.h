#pragma once
#include<iostream>
#include <deque>
#include <string>

#ifndef MYCLASS_H
#define MYCLASS_H

class ArbitraryPrecisionCalculator {

public:
    std::string consumeHandleOps(std::deque<std::string>& tokens);

    std::deque<std::string> reOrderFromLargeToSmall(std::string num1, std::string num2);


    std::string addition(std::string& num1, std::string& num2);
    std::string subtraction(std::string& num1, std::string& num2);
    std::string multiplication(std::string& num1, std::string& num2);

    std::string factorial(std::string & num1);

    std::string exponentiation(std::string& num1, std::string& num2);
    std::string division(std::string& num1, std::string& num2);
    std::string modulo(std::string& numerator, std::string& denominator);


};

#endif
