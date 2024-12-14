#pragma once
#include <string>
#include <deque>
#include <unordered_set>

class Tokenizer
{
private:
    std::unordered_set<char> target_ops;
    std::string trimOffSPaces(const std::string& input);
     bool tokenizer(char character);

public:
    Tokenizer(std::unordered_set<char> target_ops);
    std::deque<std::string> inputParser(const std::string& input);
};
