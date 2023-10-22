#ifndef PARSER_H
#define PARSER_H

#include <memory>
#include <vector>

#include "../stmt/Stmt.h"
#include "../expr/Expr.h"
#include "Token.h"

class Parser {
    private:
        std::vector<Token>& tokens;
        int current;

        Token previous();
        Token peek();
        Token advance();

        Token consume(TokenType::Type expectedType, std::string errorMsg);

        bool isAtEnd();
        bool check(TokenType::Type type);
        bool match(TokenType::Type type);

        std::unique_ptr<Stmt> declaration();
        std::unique_ptr<Stmt> statement();
        std::unique_ptr<Stmt> assignmentStatement();

        std::unique_ptr<Expr> expression();

    public:
        Parser(std::vector<Token>& tokens);

        std::vector<std::unique_ptr<Stmt>> parse();
};

#endif