/**
 * @file Parser.h
 * @author Westly Bouchard (westly_bouchard@mines.edu)
 * @brief Mash's recursive descent parser
 * @version 0.1
 * @date 2023-10-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */

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
        void retreat();

        Token consume(TokenType::Type expectedType, std::string errorMsg);

        bool isAtEnd();
        bool check(TokenType::Type type);
        bool match(TokenType::Type type);

        void synchronize();

        std::unique_ptr<Stmt> declaration();
        std::unique_ptr<Stmt> statement();
        std::unique_ptr<Stmt> assignmentStatement();

        std::unique_ptr<Expr> expression();
        std::unique_ptr<Expr> equality();
        std::unique_ptr<Expr> comparison();
        std::unique_ptr<Expr> term();
        std::unique_ptr<Expr> factor();
        std::unique_ptr<Expr> unary();
        std::unique_ptr<Expr> primary();

    public:
        Parser(std::vector<Token>& tokens);

        std::vector<std::unique_ptr<Stmt>> parse();
};

#endif
