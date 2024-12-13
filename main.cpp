#include <iostream>
#include "ArbitraryPrecisionCalculator.h"
#include "tokenizer.h"
#include <string>

using namespace std;

class REPL {
    private:
    std::string payload;

    public:
    std::string getCmdInput(){
        std::string current_input;
        cout << ">>> ";
        getline(cin, current_input);  // Read the entire line, including spaces
        return current_input;
    };

    void run(){
        while (true){
            std::string input = this->getCmdInput ();

            if(input == "exit")
            {
                this->exitPrompt();
                break;
            }

            this->process_input (input);
        }
    }

    void process_input(std::string& input){

    }

    void exitPrompt(){
        cout<< "Exiting REPL";
    };

        REPL(){
            this->run ();
        }
};


int main()
{
    const std::deque<char> target_ops = {'+','-','*', '/','%','!', '^'};

    // REPL MyREPL;
    Tokenizer *mytokenizer = new Tokenizer(target_ops);

    std::deque<std::string> tokens = mytokenizer->inputParser("32/4");
    // 308*245
        // deque<string> tokens = mytokenizer->inputParser ("30-5-6");

    ArbitraryPrecisionCalculator MyCalculatorClass;

    // 25
    MyCalculatorClass.display (MyCalculatorClass.consumeHandleOps(tokens));

    return 0;
}
