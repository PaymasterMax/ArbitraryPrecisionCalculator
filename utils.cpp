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

    size_t pos = target_value.find_first_not_of("0");

    return (pos == std::string::npos) ? "0" : target_value.substr(pos);
}

// // Find the maximum element in a deque
// template <typename T>
// T find_max(const std::deque<T>& deque) {
//     if (deque.empty()) {
//         throw std::out_of_range("Deque is empty.");
//     }
//     return *std::max_element(deque.begin(), deque.end());
// }
