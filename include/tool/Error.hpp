#include <stdexcept>
#include <string>

namespace mash {

    class LexError : public std::exception {
        private:
            std::string message;

        public:
            LexError(std::string message) : message(message) {}

            const char* what() { return message.c_str(); }
    };

    class ParseError : public std::exception {
        private:
            std::string message;

        public:
            ParseError(std::string message) : message(message) {}

            const char* what() { return message.c_str(); }
    };
    
    class RuntimeError : public std::exception {
        private:
            std::string message;

        public:
            RuntimeError(std::string message) : message(message) {}

            const char* what() { return message.c_str(); }
    };
    
}