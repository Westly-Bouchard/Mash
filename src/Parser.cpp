
#include "../include/Parser.h"

#include "../include/ASTCommon.h"

Parser::Parser(std::vector<Token> *tokens) {
    this->tokens = tokens;
    this->current = 0;
}

std::vector<Stmt>* Parser::parse() {
    std::vector<Stmt> statements;

    while (!isAtEnd()) {
        if (match(Type::INT)
            || match(Type::DOUBLE)
            || match(Type::STRING_T)
            || match(Type::BOOLEAN)
        ) {
            // If we have matched these data type tokens, then we must be looking at a variable
            // declaration
            statements.push_back(declaration());
        }

        // As per the grammar, if we did not match a variable declaration, we try to parse a
        // statement
        statements.push_back(statement());
    }
}

Stmt Parser::declaration() {
    return Binary();
}

Token Parser::peek() {
    return tokens->at(current);
}

Token Parser::previous() {
    return tokens->at(current - 1);
}

Token Parser::advance() {
    if (!isAtEnd()) current++;
    return previous();
}

bool Parser::match(Type type) {
    if (check(type)) {
        advance();
        return true;
    }

    return false;
}

bool Parser::isAtEnd() {
    return peek().type == Type::MASH_EOF;
}

bool Parser::check(Type type) {
    if (isAtEnd()) return false;
    return peek().type == type;
}
