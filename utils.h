#ifndef UTILS_H
#define UTILS_H

#include <deque>
#include <string>
#include<deque>
#include<iostream>

// Utility function to pop and return the front element of a deque
template <typename T>
T pop_and_return(std::deque<T>& deque) {
    if (deque.empty()) {
        // return NULL;
        throw std::out_of_range("Deque is empty.");
    }
    T item = deque.front();  // Capture the front item
    deque.pop_front();       // Remove the front item
    return item;             // Return the popped item
}


template <typename T>
T pop_and_return_queue(std::deque<T>& deque) {
    if (deque.empty()) {
        throw std::out_of_range("Deque is empty.");
    }
    T item = deque.front();  // Capture the front item
    deque.pop_front();       // Remove the front item
    return item;             // Return the popped item
}


// Utility function to print a deque
template <typename T>
void print_deque(const std::deque<T>& deque) {
    for (const T& item : deque) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}


// Utility function to find the maximum element in a deque
// template <typename T>
// T find_max(const std::deque<T>& deque);


std::string paddWithZeros(std::string &, int);


int compare(std::string value_1, std::string value_2);

std::string remove_leading_zeros(std::string target_value);

#endif // UTILS_H
