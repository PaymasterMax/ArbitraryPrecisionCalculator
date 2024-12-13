#pragma once
#include<iostream>
#include <deque>
#include <string>

#ifndef MYCLASS_H
#define MYCLASS_H

class ArbitraryPrecisionCalculator {

public:
    void display(const std::string &display_content);

    std::string consumeHandleOps(std::deque<std::string>& tokens);

    std::deque<std::string> reOrderFromLargeToSmall(std::string num1, std::string num2);

    std::string strRev(const std::string& string_to_rev);


    std::string addition(std::string& num1, std::string& num2);
    std::string subtraction(std::string& num1, std::string& num2);
    std::string multiplication(std::string& num1, std::string& num2);

    std::string factorial(std::string num1);

    std::string exponentiation(std::string num1, std::string num2);
    std::string division(std::string num1, std::string num2);
    // std::string modulo(std::string num1, std::string num2);


};

#endif
