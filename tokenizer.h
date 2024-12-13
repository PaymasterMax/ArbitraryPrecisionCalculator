#pragma once
#include <string>
#include <deque>

class Tokenizer
{
private:
    std::deque<char> target_ops;
    std::string trimOffSPaces(const std::string& input);
     bool tokenizer(char character);

public:
    Tokenizer(std::deque<char> target_ops);
    std::deque<std::string> inputParser(const std::string& input);
};
