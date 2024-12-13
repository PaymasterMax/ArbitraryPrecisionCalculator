#include <string>
#include "tokenizer.h"
#include <deque>
#include <regex>

Tokenizer::Tokenizer(std::deque<char> target_ops) {
    this->target_ops = target_ops;
}


std::string Tokenizer::trimOffSPaces(const std::string& input){
    return std::regex_replace(input, std::regex("\\s*([+\\-*/])\\s*"), "$1");
}

bool Tokenizer::tokenizer(char character){
    for(auto op : this->target_ops){
        if(op == character){
            return true;
        }
    }
    return false;
}

std::deque<std::string> Tokenizer::inputParser(const std::string& input){
    std::deque<std::string> tokens;
    std::string current_token;

    for(auto& input_char:  this->trimOffSPaces (input)){
        if(this->tokenizer (input_char)){
            std::string ops_str;
            ops_str.push_back (input_char);

            tokens.push_back (current_token);
            tokens.push_back (ops_str);
            current_token = "";
            continue;
        }

            current_token.push_back (input_char);
    }

    if(current_token != "") tokens.push_back ((current_token));

    return tokens;
}



