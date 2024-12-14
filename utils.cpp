#include "utils.h"
#include <string>

std::string paddWithZeros(std::string & num, int count){
    std::string alted_num = num;

    for(auto i=0; i < count; ++i)
        alted_num += "0";

    return alted_num;
}


int compare(std::string value_1, std::string value_2) {
    if (value_1.length() != value_2.length())
        return value_1.length() > value_2.length() ? 1 : -1;
    return value_1.compare(value_2);
}

std::string remove_leading_zeros(std::string target_value) {

    size_t position = target_value.find_first_not_of("0");

    return (position == std::string::npos) ? "0" : target_value.substr(position);
}

// display function implementation
void display(const std::string& display_content){
    // display the content passed.
    std::cout<<display_content<<std::endl;
}

// reverse string
std::string strRev (const std::string& str_rev){
    // Reverse the string
    return std::string(str_rev.rbegin (), str_rev.rend ());
}