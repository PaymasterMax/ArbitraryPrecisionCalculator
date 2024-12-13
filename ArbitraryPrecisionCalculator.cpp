#include<iostream>
#include "ArbitraryPrecisionCalculator.h"
#include <deque>
#include "utils.h"
#include <string>

// reverse string
std::string ArbitraryPrecisionCalculator::strRev (const std::string& str_rev){
    return std::string(str_rev.rbegin (), str_rev.rend ());
}

// display method
void ArbitraryPrecisionCalculator::display(const std::string& display_content){

    std::cout<<display_content<<std::endl;
}


std::deque<std::string> ArbitraryPrecisionCalculator::reOrderFromLargeToSmall(std::string num1, std::string num2){
    std::deque<std::string> opsNumbers;

    if(num1.size ()> num2.size ()){
        opsNumbers.push_back (num1);
        opsNumbers.push_back (num2);
    }else if (num2.size ()>num1.size ()){
        opsNumbers.push_back (num2);
        opsNumbers.push_back (num1);
    }
    else {
        if(num1>num2){
            opsNumbers.push_back (num1);
            opsNumbers.push_back (num2);
        }else{
            opsNumbers.push_back (num2);
            opsNumbers.push_back (num1);
        }
    }

    return  opsNumbers;
}

std::string ArbitraryPrecisionCalculator::addition(std::string& num1, std::string& num2){
    std::deque<std::string> orderedNums = this->reOrderFromLargeToSmall (num1, num2);
    const std::string longestNo = this->strRev(orderedNums.at(0));
    const std::string shortestNo = this->strRev(orderedNums.at (1));

    std::string results = "";

    char carry = '0';

    const int shortest_no_length = shortestNo.size();
        const int longest_no_length = longestNo.size();


    for(size_t i=0; i<longest_no_length; ++i){

        if((shortest_no_length-1)>=i){
            // single character or 2 digit character stored in col_res
            std::string col_res = std::to_string ((longestNo.at(i) - '0') + (shortestNo.at (i) - '0') + (carry-'0'));

            if(col_res.size () >1){
                carry = '1';
                results.push_back(col_res.at (1));
            }else{
                results.push_back(col_res.at (0));
                carry = '0';
            }

        }else{
            std::string col_res = std::to_string((longestNo.at(i) - '0') + (carry-'0'));
            if(col_res.size () >1){
                carry = '1';
                results.push_back(col_res.at(1));

            }else{
                results.push_back (col_res.at(0));
                carry = '0';
            }
        }

        // if we ave reached end of loop, push the carry infront of the character
        if((i+1) == longest_no_length && (carry-'0')>0){
            results.push_back (carry);
        }
    }

    // cout<<num1<<" + "<<num2<<" = "<<this->strRev (results)<<endl;

    return this->strRev (results);
}



std::string ArbitraryPrecisionCalculator::subtraction(std::string& num1, std::string& num2){
    std::deque<std::string> orderedNums = this->reOrderFromLargeToSmall (num1, num2);
    const std::string longestNo = this->strRev(orderedNums.at(0));
    const std::string shortestNo = this->strRev(orderedNums.at (1));

    std::string results = "";

    char borrow = '0';

    const int shortest_no_length = shortestNo.size();
    const int longest_no_length = longestNo.size();


    for(size_t i=0; i<longest_no_length; ++i){

        if((shortest_no_length-1) >= i){
            // single character or 2 digit character stored in col_res
            std::string col_res;

            if((longestNo.at(i) - '0') >= ((shortestNo.at (i) - '0') + ( borrow - '0'))){
                col_res.append(std::to_string (((longestNo.at(i) - '0') - ((shortestNo.at (i) - '0')+(borrow-'0')))));
                borrow = '0';

            }else{
                col_res.append(std::to_string(((longestNo.at (i)-'0') + 10) -  (shortestNo.at (i) - '0') - ( borrow - '0')) );

                borrow='1';

            }

            results.append (col_res);
        }else{
            std::string col_res;

            if((longestNo.at(i) - '0')>= ( borrow - '0')){
                col_res.append(std::to_string (((longestNo.at(i) - '0') - (borrow-'0'))));
                borrow = '0';
            }else{
                col_res.append(std::to_string(((longestNo.at(i) - '0') + 10) - (borrow-'0')));
                borrow='1';
            }
            results.append (col_res);
        }

        // if we ave reached end of loop, push the carry infront of the character
        if(( i + 1) == longest_no_length && (borrow-'0')>=0){
            // cout<<"Results: "<<this->strRev (results)<<endl;
            // results.push_back (borrow);
        }
    }

    return this->strRev (results);
}

std::string ArbitraryPrecisionCalculator::multiplication (std::string& num1, std::string& num2){
    std::deque<std::string> orderedNums = this->reOrderFromLargeToSmall (num1, num2);
     std::string longestNo = orderedNums.at(0);
     std::string shortestNo = this->strRev (orderedNums.at (1));

     std::deque<std::string> sub_res = {};


    char carry='0';

    const int shortest_no_length = shortestNo.size();

    if(shortest_no_length == 1){
        std::string results = "";

        for(auto & curr_no: this->strRev (longestNo)) {

            std::string tmp_num1 = std::to_string((curr_no - '0') * (shortestNo.at (0) - '0'));
            std::string tmp_num2 = std::string(1, carry);

            std::string tmp_res = this->addition (tmp_num1, tmp_num2);

            // std::cout<<curr_no<<" * "<<shortestNo.at (0);

            if (tmp_res.size() > 1) {
                results =  std::string(1, tmp_res.at(1)) + results;
                carry = tmp_res.at(0);
            } else {
                carry = '0';

                results = tmp_res + results;
            }

            // std::cout<<" = "<<tmp_res<<" Carry=>"<<carry<<std::endl;
        }

        if(carry != '0'){
            results = (std::string(1, carry)) + results;
            carry = '0';
        }

        // std::cout<<" Final = " <<results<<std::endl;

        sub_res.push_back (results);
        results="";


    }else{

        for(auto & single_small_col: shortestNo){
            std::string single_small_col_mod = std::string(1,single_small_col);
            sub_res.push_back(this->multiplication (longestNo, single_small_col_mod));

            // std::cout<<single_small_col<<"Small num: "<<this->multiplication (longestNo, single_small_col_mod)<<std::endl;
        }
    }

    if(carry != '0'){
        sub_res.push_front (std::string(1, carry));
        carry = '0';
    }

    std::string tmp_res="0";

    // for(auto & curr_res: sub_res){
    for(auto i=0; i<sub_res.size (); ++i){
        auto curr_res = sub_res.at (i);

        const int tmp_res_no_length = tmp_res.size();
        const int curr_no_length = curr_res.size();

        // if(tmp_res.at (0)-'0'== 0){

            // std::cout<<curr_res<<std::endl;
            // tmp_res = curr_res;
            // continue;
        // }

        // std::cout<<"Tmp res: "<<tmp_res<<" Curr res: "<<curr_res<<std::endl;

        // tmp_res = tmp_res_no_length<curr_no_length ?
        //               paddWithZeros(tmp_res, curr_no_length -  tmp_res_no_length) :
        //               tmp_res;

        if(i != 0)
            curr_res = paddWithZeros(curr_res, i);

        // std::cout<<curr_res<<" "<<std::endl;


        // std::cout<<"";

        tmp_res = this->addition (
            tmp_res,
            curr_res
            );
    }

    // std::cout<<num1<<"*"<<num2<<" = "<<tmp_res<<std::endl;

    return tmp_res;
}


std::string ArbitraryPrecisionCalculator::factorial(std::string num){
    std::string result = "1"; // starting value for results to avoid making the factorial multiplication results to 0
    std::string decrement_value = "1";

    while (num != "0") {
        // Multiply previous results by num
        result = this->multiplication(result, num);

        // Decrement num and reassign it to itself till it gets to 0, where the loop breaks out.
        num = this->subtraction (num, decrement_value);
    }

    return result;
}

std::string ArbitraryPrecisionCalculator::exponentiation(std::string exp_base, std::string exponent){
    // general cases
    // any number with base as 0 is always is awlays 0
    if(exp_base == "0")
        return "0";

    // any number with exponent as 0 is always 1
    if(exponent == "0")
        return "1";

    // initial the results to be 1 to prevent from making the overall result to zero since (any-number * 0 = 0)
    std::string results = "1";

    std::string exp_decrement_value = "1";

    // loop till the exponent is 0
    while (exponent != "0") {
        // multiply the results by the base untill the exponent becomes 0
        results = this->multiplication (results, exp_base);

        // decrement the base to update it's value after multiplication
        // operations has been done.
        exponent = this->subtraction (exponent, exp_decrement_value);
    }

    return results;
}

std::string ArbitraryPrecisionCalculator::division(std::string numerator, std::string denominator){

    // handle edge case
    if(denominator == "0") throw std::invalid_argument("Division by 0 Error");

    // 0 divided by any number is 0
    if(numerator == "0") return "0";


    std::string quotient = "";
    std::string current = "";

    for (char digit : numerator) {
        current += digit;  // Append the next digit to the current portion

        // Find how many times divisor fits into current
        int count = 0;
        while (compare(current, denominator) >= 0) {  // While current >= divisor
            current = this->subtraction(current, denominator);
            count++;
        }

        quotient += std::to_string(count);  // concatenate count to quotient
    }

    // Remove leading zeros in the result
    return remove_leading_zeros(quotient);

}

std::string ArbitraryPrecisionCalculator::consumeHandleOps(std::deque<std::string>& tokens){
    std::deque<std::string> single_arithma = {};

    for(auto& curr_token: tokens){
        single_arithma.push_back(curr_token);

        // operations with 3 operands
        if(single_arithma.size() == 3){

            std::string num1 = pop_and_return (single_arithma);
            std::string ops = pop_and_return (single_arithma);
            std::string num2 = pop_and_return (single_arithma);


            if(ops == "+")
                single_arithma.push_back (this->addition (num1, num2));

            if(ops == "-")
                single_arithma.push_back (this->subtraction(num1, num2));

            if(ops == "*")
                single_arithma.push_back (this->multiplication(num1, num2));

            if(ops == "^")
                single_arithma.push_back (this->exponentiation(num1, num2));

            if(ops == "/")
                single_arithma.push_back (this->division(num1, num2));


        }

        // operations with 2 operands
        // else if(single_arithma.size () == 2){
        //     std::string num1 = pop_and_return (single_arithma);
        //     std::string ops = pop_and_return (single_arithma);

        //     if(ops == "!")
        //         single_arithma.push_back (this->factorial(num1));

        // }
    }

    if(single_arithma.size ()>1)
        return this->consumeHandleOps (single_arithma);

    return pop_and_return (single_arithma);
}

