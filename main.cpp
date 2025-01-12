#include <unordered_set>
#include <iostream>
#include <memory>
#include <string>

// dev cpp files
#include "ArbitraryPrecisionCalculator.h"
#include "tokenizer.h"
#include "utils.h"

using namespace std;

class REPL {
private:
    const std::unordered_set<char> target_ops = {'+', '-', '*', '/', '%', '!', '^'};
    std::unique_ptr<ArbitraryPrecisionCalculator> MyCalculatorClass;
    std::unique_ptr<Tokenizer> tokenizer;

public:
    REPL()
        : MyCalculatorClass(std::make_unique<ArbitraryPrecisionCalculator>()),
          tokenizer(std::make_unique<Tokenizer>(target_ops)) {
        this->run();
    }

    ~REPL() = default; // Smart pointers handle cleanup automatically.

    std::string getCmdInput() {
        std::string current_input;
        std::cout << ">>> ";
        std::getline(std::cin, current_input);
        return current_input;
    }

    void process_input(std::string& input) {
        try {
            // Tokenize the input
            auto parsedInput = tokenizer->inputParser(input);

            // Process the tokens
            auto processedOutput = MyCalculatorClass->consumeHandleOps(parsedInput);

            // Display the result
            display(processedOutput);

        } catch (const std::exception& e) {

            // get the error with the error.what method call
            std::cout << "Error: " << e.what() << std::endl;
        }
    }

    void exitPrompt() {
        std::cout << "Exiting REPL. Goodbye." << std::endl;
    }

    void run() {
        while (true) {
            try {
                std::string input = this->getCmdInput();
                if (input == "exit") {
                    this->exitPrompt();
                    break;
                }
                this->process_input(input);
            } catch (const std::exception& e) {
                std::cout << "Critical error: " << e.what() << std::endl;
                break;
            }
        }
    }
};


int main()
{

    REPL MyREPL;
    return 0;
}
