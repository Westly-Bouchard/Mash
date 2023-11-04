#include <stdexcept>
#include <string>

#include "../core/Token.h"

namespace mash {

    class LexError : public std::exception {
        private:
            std::string message;
            int line;

        public:
            LexError(std::string message, int line) : message(message), line(line) {}

            const char* what() {
                std::string temp = "Encountered error on line " + line + '\n';
                temp += message;
                
                return message.c_str();
            }
    };

    class ParseError : public std::exception {
        private:
            std::string message;
            Token symbol;

        public:
            ParseError(std::string message, Token symbol) : message(message), symbol(symbol) {}

            const char* what() {
                std::string temp = "Encountered Error on line " + symbol.line + '\n';
                temp += message;

                return temp.c_str();
            }
    };
    
    class RuntimeError : public std::exception {
        private:
            std::string message;

        public:
            RuntimeError(std::string message) : message(message) {}

            const char* what() { return message.c_str(); }
    };
    
}