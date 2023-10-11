#ifndef PARSER_H
#define PARSER_H

#include <memory>
#include <vector>

#include "stmt/Stmt.h"
#include "Token.h"

using namespace TokenType;

class Parser {
    private:
        std::vector<Token>& tokens;
        int current;

        Token previous();
        Token peek();
        Token advance();

        bool isAtEnd();
        bool check(Type type);
        bool match(Type type);

        std::unique_ptr<Stmt> declaration();
        std::unique_ptr<Stmt> statement();

    public:
        Parser(std::vector<Token>& tokens);

        vector<std::unique_ptr<Stmt>> parse();
};

#endif