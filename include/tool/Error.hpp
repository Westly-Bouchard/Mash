#include <stdexcept>
#include <string>
#include <sstream>

#include "../core/Token.h"

namespace mash {

    class LexError : public std::exception {
        private:
            std::string message;

        public:
            LexError(std::string message, int line) {
                std::stringstream temp;
                temp << "Encountered error on line: " << line << std::endl;
                temp << message;
                this->message = temp.str();
            }

            const char* what() const noexcept override {
                return message.c_str();
            }
    };

    class ParseError : public std::exception {
        private:
            std::string message;

        public:
            ParseError(std::string message, Token symbol) {
                std::stringstream temp;
                temp << "Encountered error at token '" + symbol.lexeme + "' on line " << symbol.line;
                temp << std::endl << message;
                this->message = temp.str();
            }

            const char* what() const noexcept override {
                return message.c_str();
            }
    };
    
    class RuntimeError : public std::exception {
        private:
            std::string message;

        public:
            RuntimeError(std::string message) : message(message) {}

            const char* what() const noexcept override { return message.c_str(); }
    };
    
}