#include<iostream>
#include "ArbitraryPrecisionCalculator.h"
#include <deque>
#include "utils.h"
#include <string>

// display method

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
    const std::string longestNo = strRev(orderedNums.at(0));
    const std::string shortestNo = strRev(orderedNums.at (1));

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

    return strRev (results);
}



std::string ArbitraryPrecisionCalculator::subtraction(std::string& num1, std::string& num2){
    std::deque<std::string> orderedNums = this->reOrderFromLargeToSmall (num1, num2);
    const std::string longestNo = strRev(orderedNums.at(0));
    const std::string shortestNo = strRev(orderedNums.at (1));

    std::string results = "";

    char borrow = '0';

    const int shortest_no_length = shortestNo.size();
    const int longest_no_length = longestNo.size();


    for(size_t i=0; i<longest_no_length; ++i){

        if((shortest_no_length-1) >= i){
            // single character or 2 digit character stored in col_res
            std::string col_res;

            // check if the character in the shortest number is greater than the character in the longest number
            if((longestNo.at(i) - '0') >= ((shortestNo.at (i) - '0') + ( borrow - '0'))){
                // append the character to the result
                col_res.append(std::to_string (((longestNo.at(i) - '0') - ((shortestNo.at (i) - '0')+(borrow-'0')))));
                // reset the borrow
                borrow = '0';

            }else{
                // append the character to the result after the subtraction and factoring in of borrow value
                col_res.append(std::to_string(((longestNo.at (i)-'0') + 10) -  (shortestNo.at (i) - '0') - ( borrow - '0')) );

                // set the borrow to 1
                borrow='1';

            }

            // append the result to the results string
            results.append (col_res);
        }else{
            // define the column result
            std::string col_res;

            //  check if the value in the current column is greater than the borrow value
            if((longestNo.at(i) - '0')>= ( borrow - '0')){
                // append the character to the result
                col_res.append(std::to_string (((longestNo.at(i) - '0') - (borrow-'0'))));
                // reset the borrow
                borrow = '0';
            }else{
                // append the character to the result after the subtraction and factoring in of borrow value
                col_res.append(std::to_string(((longestNo.at(i) - '0') + 10) - (borrow-'0')));
                // set the borrow to 1
                borrow='1';
            }
            // append the result to the results string
            results.append (col_res);
        }

        // if we ave reached end of loop, push the carry infront of the character
        if(( i + 1) == longest_no_length && (borrow-'0')>=0){
            // cout<<"Results: "<<this->strRev (results)<<endl;
            // results.push_back (borrow);
        }
    }

    // return the result after reversing it, the numbers are worked on from the reverse order.
    // since the natural order of the numbers is from left to right, we need to reverse the result
    // and remove leading zeros.
    return remove_leading_zeros(
        strRev(results));
}

std::string ArbitraryPrecisionCalculator::multiplication (std::string& num1, std::string& num2){
    // order the numbers based on their lengths
    std::deque<std::string> orderedNums = this->reOrderFromLargeToSmall (num1, num2);
    // set the longestNo
     std::string longestNo = orderedNums.at(0);
    //  set and reverse the shortestno to achieve the natural way of handling numbers
     std::string shortestNo = strRev (orderedNums.at (1));

    // intialize the sub_res to store the dequeue of sub results per column.
     std::deque<std::string> sub_res = {};

    // initialize the carry value to 0
    char carry='0';

    // get the size of the shortest number
    const int shortest_no_length = shortestNo.size();

    // check if the length of the shortest number is 1.
    if(shortest_no_length == 1){
        // if it is, return the multiplication of the two numbers(the shortest number
        std::string results = "";

    // iterate through the reversed longest number.
        for(auto & curr_no: strRev (longestNo)) {

            // multiply each of the column of longest number with the single shortest number.
            std::string tmp_num1 = std::to_string((curr_no - '0') * (shortestNo.at (0) - '0'));

            // conver the carry char field to string so as to perform addition operation on it.
            std::string tmp_num2 = std::string(1, carry);

            // add the two numbers together and store the result in the sub_res.
            std::string tmp_res = this->addition (tmp_num1, tmp_num2);

            // std::cout<<curr_no<<" * "<<shortestNo.at (0);

            // check if the length of the temporary results for current longestNo column is larger than 1.
            if (tmp_res.size() > 1) {
                // if it is, append the temporary results at index 1 to the beginning of sub_res.
                results =  std::string(1, tmp_res.at(1)) + results;

                // append the carry value to the sub_res(Digit in the first position from the results)
                carry = tmp_res.at(0);
            } else {
                // reset the carry value to 0
                carry = '0';
                // update the results by appending the new current col result to the previous accumulated results value.
                results = tmp_res + results;
            }

            // std::cout<<" = "<<tmp_res<<" Carry=>"<<carry<<std::endl;
        }

    // check if after the operation if the carry value has any value set.
        if(carry != '0'){
            // if so, append the carry value to the resulting accumulated result and reassign it back to results.
            results = (std::string(1, carry)) + results;

            // reset the carry value.
            carry = '0';
        }

        // std::cout<<" Final = " <<results<<std::endl;

        // push the single digit, longestNo(column wise multiplication) to the overall
        // results of each column in the shortest number.
        sub_res.push_back (results);
        // reset the results for the next iteration.
        results="";
    }else{
        // iterate through the shortest number
        for(auto & single_small_col: shortestNo){
            // convert the single_small_col from char to string since multiplication method needs the params to be string.
            std::string single_small_col_mod = std::string(1,single_small_col);

            // for each number recursively call the multiplication method passing in the longestNo, and the single digit in each iteration.
            // finally append all the outputs for each column to the overall results.
            sub_res.push_back(this->multiplication (longestNo, single_small_col_mod));

            // USED FOR DEBUGGING
            // std::cout<<single_small_col<<"Small num: "<<this->multiplication (longestNo, single_small_col_mod)<<std::endl;
        }
    }
    // check if in the current carry value has any value set.
    if(carry != '0'){
        // if it has push the value to the front of the sub_res variable
        sub_res.push_front (std::string(1, carry));

        // reset the carry field to 0.
        carry = '0';
    }

    // define a variable to compute the results of each column.
    std::string tmp_res="0";

    // iterate through the sub_res queue
    for(auto i=0; i<sub_res.size (); ++i){
        // for each number in the queue, get the number in the current inde and add it to the tmp_res variable.
        auto curr_res = sub_res.at (i);

        // get the size of the tmp_res_no_lenght
        const int tmp_res_no_length = tmp_res.size();

        // get the size of the current_res_no_length
        const int curr_no_length = curr_res.size();

    // check if the index of the current iteration is not 0, if it's not zero, carry out the addition.
        if(i != 0)
        // first padd the numbers with zeros since in multiplication
        /*
            Results would normally need this arrangement(Next column results to be offset one column to the front from previous column.) E.g:
            1 2 3 5
            |   |  |  |
        3 2 3 8
         */
            curr_res = paddWithZeros(curr_res, i);

    // perform the addition and append the result to tmp_res for next iteration addition
        tmp_res = this->addition (
            tmp_res,
            curr_res
            );
    }

    // std::cout<<num1<<"*"<<num2<<" = "<<tmp_res<<std::endl;

// return the resulting value after performing the addition.
    return tmp_res;
}

// factorial method
std::string ArbitraryPrecisionCalculator::factorial(std::string & num){
    if(num.size() == 1 && num.at(0)- '0' < 1)
        return "1";

    // factorial is a special case of multiplication.
    // if given 5!, that implies that 5*4*3*2*1.
    // so we can use the multiplication method to calculate the factorial.

    // define the decrement value to one.
    // This will be used to decrement the number in each iteration.
    std::string decrement_value = "1";

    std::string curr_num = this->subtraction(num, decrement_value);

    std::cout <<"Curr: "<<curr_num << std::endl;

    // store the output of the rest of the other factorials smaller than the current number
    std::string down_tree_fact = this->factorial(
        curr_num
        );


    // return the results of the multiplication of rest of factorials by current number.
    return this->multiplication(
        down_tree_fact,
        num
        );
}

std::string ArbitraryPrecisionCalculator::exponentiation(std::string & exp_base, std::string & exponent){
    // exponentiation is a special case of multiplication.
    // if given 2^5, that implies that 2*2*2*2 * 2
    // so we can use the multiplication method to calculate the exponentiation.

    // define the general cases
    // any number with base as 0 is always is awlays 0
    if(exp_base == "0")
        return "0";

    // any number with exponent as 0 is always 1
    if(exponent == "0")
        return "1";

        // define the decrement value
    std::string exp_decrement_value = "1";

    // decrement the exponent by 1
    std::string curr_exp = this->subtraction(
        exp_decrement_value,
        exponent
        );

    // get the down tree exponents(this means, if we start with 2^7, the results from here will be
    //  the results of 2^6)
    std::string down_tree_exp = this->exponentiation(
        exp_base,
        curr_exp
        );

    // multiply the results of the subsequent exponents by the current base.
    return this->multiplication(down_tree_exp, exp_base);
}

// division method calculator
std::string ArbitraryPrecisionCalculator::division(std::string& numerator, std::string & denominator){
    // division is a special case of subtraction
    // if given 10/2, that implies that 10 - 2 - 2 - 2 - 2 - 2
    // so we can use the subtraction method to calculate the division.

    // base cases
    if(denominator == "0") throw std::invalid_argument("Division by 0 Error");

    // 0 divided by any number is 0
    if(numerator == "0") return "0";

    // initialize the division quotients
    std::string quotient = "";

    // initialize the current digit
    std::string current = "";

    // iterate through the numerator bit
    for (char digit : numerator) {
        // Append the next digit to the current portion
        current += digit;

        // Find how many times divisor fits into current
        int count = 0;
        // compare the current digit to the denominator
        // While current >= divisor
        while (compare(current, denominator) >= 0) {
            // perform the subtraction and reassign the result to current variable.
            current = this->subtraction(current, denominator);
            // increment the count variable.
            count++;
        }

    // append the count to the quotient value.
        quotient += std::to_string(count);  // concatenate count to quotient
    }

    // Remove leading zeros in the result and return the output
    return remove_leading_zeros(quotient);

}

// modulo method.
std::string ArbitraryPrecisionCalculator::modulo(std::string& numerator, std::string &denominator){
    // base cases
    // if denominator is 0, return an error message
    if (denominator == "0") throw std::invalid_argument("Division error: Division by 0");

    // if numerator is 0, return 0
    if (numerator == "0") return "0";
    // perform comparison between numerator and denominator.
    // if numerator is less than denominator, return numerator
    if (compare(numerator, denominator) < 0) return numerator;

    // initialize the current digit.
    std::string current = "";

    // iterate through the numerator digits
    for (char digit : numerator) {
        // for each digit, append the next digit to the current portion
        current += digit;
        // compare the current number field to the denominator
        while (compare(current, denominator) >= 0) {
            // perform subtraction and reassign the result to the current variable
            current = this->subtraction(current, denominator);
        }
    }

    // remove leading zeros and return the value stored in the current value.
    return remove_leading_zeros(current);
}

// consumer method handler
std::string ArbitraryPrecisionCalculator::consumeHandleOps(std::deque<std::string>& tokens){
    // initialize the single_arithmethic portion to a dequeue
    std::deque<std::string> single_arithma = tokens; //{};

    // iterate through the tokens deque received
    // for(auto& curr_token: tokens){
    //     // push the current token to the single_arithma deque.
    //     single_arithma.push_back(curr_token);

    //     // operations with 3 operands
    //     if(single_arithma.size() == 3){

    //         std::string num1 = pop_and_return (single_arithma);
    //         std::string ops = pop_and_return (single_arithma);
    //         std::string num2 = pop_and_return (single_arithma);

    //         if(ops == "+")
    //             single_arithma.push_back (this->addition (num1, num2));

    //         if(ops == "-")
    //             single_arithma.push_back (this->subtraction(num1, num2));

    //         if(ops == "*")
    //             single_arithma.push_back (this->multiplication(num1, num2));

    //         if(ops == "^")
    //             single_arithma.push_back (this->exponentiation(num1, num2));

    //         if(ops == "/")
    //             single_arithma.push_back (this->division(num1, num2));

    //         if(ops == "%")
    //             single_arithma.push_back (this->modulo(num1, num2));
    //     }

        // operations with 2 operands
        // else if(single_arithma.size () == 2){
        //     std::string num1 = pop_and_return (single_arithma);
        //     std::string ops = pop_and_return (single_arithma);

        //     if(ops == "!")
        //         single_arithma.push_back (this->factorial(num1));

        // }
    // }

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

            if(ops == "%")
                single_arithma.push_back (this->modulo(num1, num2));


        }

        // operations with 2 operands
        else if(single_arithma.size () == 2){
            std::string num1 = pop_and_return (single_arithma);
            std::string ops = pop_and_return (single_arithma);

            if(ops == "!"){
                single_arithma.push_back (this->factorial(num1));
            }

        }

    if(single_arithma.size ()>1)
        return this->consumeHandleOps (single_arithma);

    return pop_and_return (single_arithma);
}
