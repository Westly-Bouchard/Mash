/**
 * @file Parser.cpp
 * @author Westly Bouchard (westly_bouchard@mines.edu)
 * @brief The implementation for the Mash recursive descent parser
 * @version 0.1
 * @date 2023-10-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "../../include/core/Parser.h"

#include "../../include/core/ASTCommon.h"

#include "../../include/tool/Error.hpp"

#include <iostream>

using namespace TokenType;
using namespace std;

Parser::Parser(vector<Token>& tokens) : tokens(tokens), current(0), hadError(false) {}

vector<unique_ptr<Stmt>> Parser::parse() {

    // We have to use a vector of pointers here because it's not possible to instantiate the pure
    // virtual class Stmt. But we use pointers to refer to subnodes within the tree anyways so it is
    // consistent
    vector<unique_ptr<Stmt>> statements;

    while (!isAtEnd()) {
        // While we're not at the end of the file, we try to parse a declaration, which is the,
        // highest level production in our grammar
        statements.push_back(declaration());
    }

    return statements;
}

bool Parser::getErrorState() {
    return this->hadError; 
}

std::unique_ptr<Stmt> Parser::declaration() {
    try {
        // Attempt to match these data type tokens, if we do we try to parse a variable declaration
        if (match(Type::INT)
            || match(Type::DOUBLE)
            || match(Type::STRING_T)
            || match(Type::BOOLEAN)
        ) {
            // Grab the type token
            Token type = previous();

            // Consume the token that represents the name of the variable being declared. If the next
            // token is not an identifier, then we have a syntax error and we have to handle that
            Token name = consume(Type::IDENTIFIER, "Expected name for variable declaration");

            unique_ptr<Expr> initializer = nullptr;

            // If we encounter an equals sign, then the user is also initializing the variable, and that
            // is part of the declaration statement.
            if (match(Type::EQUAL)) {
                // So we parse the expression that follows the equal sign
                initializer = expression();
            }

            // Consume the semicolon at the end of the statement, if we don't find one that's a syntax
            // error
            consume(Type::SEMICOLON, "Expected a semicolon `;` after variable declaration");

            // Return the AST node
            return make_unique<VarDecl>(type.type, name, std::move(initializer));
        }

        // As per the grammar, if we did not match a variable declaration, we try to parse a statement
        return statement();

    } catch (mash::ParseError& e) {
        cerr << e.what() << endl;
        synchronize();
        hadError = true;
        return nullptr;
    }
}

unique_ptr<Stmt> Parser::statement() {
    // To parse a statement, we will switch over the type of the current token
    if (match(Type::ECHO)) {
        // Consume the opening parentheses
        consume(Type::LEFT_PAREN, "Expected left paren `(` after library call `echo`");

        // Parse the expression to print
        // We don't need to worry about type checking here because we can echo any of the four Mash
        // datatypes
        unique_ptr<Expr> toPrint = expression();

        // Consume the closing parentheses
        consume(Type::RIGHT_PAREN, "Expected closing paren `)` after expression");

        // Consume the semicolon marking the end of the statement
        consume(Type::SEMICOLON, "Expected semicolon `;` at end of statement");

        // Construct the AST node and return it
        return make_unique<Echo>(std::move(toPrint));
    }

    if (match(Type::EXEC)) {
        // Consume the opening parentheses
        consume(Type::LEFT_PAREN, "Expected left paren `(` after library call `echo`");

        // Parse the command to run
        unique_ptr<Expr> toRun = expression();

        // It's good to be thinking about type checking at this point, but I think I'm going to move
        // that to its own pass
        unique_ptr<Expr> result = nullptr;
        if (match(Type::COMMA)) {
            // If the next token is a comma, then the user want's to store the result of the command
            // execution in a variable so we'll go ahead and parse an argument

            // We try to consume an identifier for the result
            Token resultIdentifier = consume(Type::IDENTIFIER, "Expected identifier after `,`");
            result = make_unique<Variable>(resultIdentifier);
        }

        // Consume the closing parentheses
        consume(Type::RIGHT_PAREN, "Expected closing paren `)` after library call `exec`");

        // Consume the semicolon
        consume(Type::SEMICOLON, "Expected semicolon `;` at end of statement");

        // Construct the ast node and return it
        return make_unique<Exec>(std::move(toRun), std::move(result));
    }

    if (match(Type::IF)) {
        // Consume the opening parentheses
        consume(Type::LEFT_PAREN, "Expected left paren `(` after keyword `if`");

        // Parse an expression for the condition
        unique_ptr<Expr> condition = expression();

        // Consume the closing parentheses after the expression
        consume(Type::RIGHT_PAREN, "Expected right paren `)` after expression");

        // Parse the statement for if the condition is true
        unique_ptr<Stmt> thenBranch = statement();

        // Set up a pointer in case there is an else branch
        unique_ptr<Stmt> elseBranch = nullptr;

        // If we match an else keyword, then we also need to parse an else branch statement
        if (match(Type::ELSE)) {
            elseBranch = statement();
        }

        // Construct the ast node and return it
        return make_unique<If>(std::move(condition), std::move(thenBranch), std::move(elseBranch));
    }

    if (match(Type::WHILE)) {
        // Consume the opening parentheses
        consume(Type::LEFT_PAREN, "Expected left paren `(` after keyword `while`");

        // Parse the loop condition
        unique_ptr<Expr> condition = expression();

        // Consume the closing parentheses
        consume(Type::RIGHT_PAREN, "Expected right paren `)` after expression");

        // Parse the statement that the loop will actually run every time
        unique_ptr<Stmt> loopStmt = statement();

        // Construct the ast node and return it
        return make_unique<While>(std::move(condition), std::move(loopStmt));
    }

    if (match(Type::FOR)) {
        // Consume opening parentheses
        consume(Type::LEFT_PAREN, "Expected left paren `(` after keyword `for`");

        // Parse the loop condition
        unique_ptr<Expr> condition = expression();

        // Consume the closing parentheses
        consume(Type::RIGHT_PAREN, "Expected right paren `)` after expression");

        // Parse the looping statement itself
        unique_ptr<Stmt> loopStmt = statement();

        // Construct the ast node and return it
        return make_unique<For>(std::move(condition), std::move(loopStmt));
    }

    if (match(Type::LEFT_BRACE)) {
        // Set up a vector to hold the statements
        vector<unique_ptr<Stmt>> statements;

        // Parse statements until we find a right brace or the end of the file
        while (!check(Type::RIGHT_BRACE) && !isAtEnd()) {
            statements.push_back(declaration());
        }

        consume(Type::RIGHT_BRACE, "Expected right brace '}' after block statement");

        // Construct the ast node and return it
        return make_unique<Block>(std::move(statements));
    }

    // If we didn't match any of these, we'll assume that we have an assignment
    return assignmentStatement();
}

unique_ptr<Stmt> Parser::assignmentStatement() {
    // If we have an assignment statement, then the next token should be an identifier, followed by
    // an equals sign and an expression

    // That's one pretty nice feature of such a small language like this that doesn't have classes
    // or even functions, we don't have to worry about any other type of statement after we've
    // checked all of the important ones, cause literally the only other thing it could be is an
    // assignment statement

    // Another shortcut we get from this is that the only possible lvalue we could ever have is just
    // an identifier. This means that, to determine if the current statement is an assignment, all
    // we have to do is check for an identifier followed by an equals sign

    // If we match an identifier
    if (match(Type::IDENTIFIER)) {
        // If the next token is an equals sign, we will try to parse an assignment
        if (check(Type::EQUAL)) {
            // We grab the identifier token to construct the ast node later
            Token name = previous();

            // We consume the equals sign
            consume(Type::EQUAL, "Expected equals `=` after identifier");

            // Parse the rvalue as an expression
            unique_ptr<Expr> expr = expression();

            // Consume the semicolon at the end of the statement
            consume(Type::SEMICOLON, "Expected semicolon `;` after expression");

            // Construct the ast node and return it
            return make_unique<VarAssign>(name, std::move(expr));
        } else {
            // If the nex token is not an equals sign, then we need to back-track, and try to parse
            // an expresion statement

            // To be honest I don't feel great about adding this function, as I could see it
            // potentially causing a lot of problems. As this is a recursive descent parser, it's
            // really not supposed to go backwards at all. We'll see if it breaks anything though ig
            retreat();
        }
    }

    // If we're at this point, we can be sure that the only thing left to attempt to parse is an
    // expression statement AND that the current token is the same as it was at the beginning of the
    // function. This is an important caveat to ensure that the expression is pared correctly
    unique_ptr<Expr> expr = expression();

    consume(Type::SEMICOLON, "Expected semicolon `;` after expression statement");

    return make_unique<Expression>(std::move(expr));
}

unique_ptr<Expr> Parser::expression() {
    // TBH this function is really just a wrapper around equality cause it's easier to conceptualize
    return equality();
}

unique_ptr<Expr> Parser::equality() {
    // The first thing we do is try to parse the left hand side of the equality, which will be a
    // comparison
    unique_ptr<Expr> expr = comparison();

    while (match(Type::BANG_EQUAL) || match(Type::EQUAL_EQUAL)) {
        Token op = previous();
        unique_ptr<Expr> right = comparison();
        expr = make_unique<Binary>(std::move(expr), op, std::move(right));
    }

    return expr;
}

unique_ptr<Expr> Parser::comparison() {
    unique_ptr<Expr> expr = term();

    while (
        match(Type::GREATER) || match(LESS) || match(GREATER_EQUAL) || match(LESS_EQUAL)
    ) {
        Token op = previous();
        unique_ptr<Expr> right = term();
        expr = make_unique<Binary>(std::move(expr), op, std::move(right));
    }

    return expr;
}

unique_ptr<Expr> Parser::term() { 
    unique_ptr<Expr> expr = factor();

    while (match(Type::MINUS) || match(Type::PLUS)) {
        Token op = previous();
        unique_ptr<Expr> right = factor();
        expr = make_unique<Binary>(std::move(expr), op, std::move(right));
    }

    return expr;
}

unique_ptr<Expr> Parser::factor() {
    unique_ptr<Expr> expr = unary();

    while (match(Type::SLASH) || match(Type::STAR)) {
        Token op = previous();
        unique_ptr<Expr> right = unary();
        expr = make_unique<Binary>(std::move(expr), op, std::move(right));
    }

    return expr;
}

unique_ptr<Expr> Parser::unary() {
    if (match(Type::BANG) || match(Type::MINUS)) {
        Token op = previous();
        unique_ptr<Expr> right = unary();
        return make_unique<Unary>(op, std::move(right));
    }

    return primary();
}

unique_ptr<Expr> Parser::primary() {
    if (match(Type::FALSE)) return make_unique<Literal>(false);
    if (match(Type::TRUE)) return make_unique<Literal>(true);

    if (match(Type::NUMBER_DOUBLE)) return make_unique<Literal>(previous().literal);

    if (match(Type::NUMBER_INT)) return make_unique<Literal>(previous().literal);

    if (match(Type::STRING)) return make_unique<Literal>(previous().literal);

    if (match(Type::IDENTIFIER)) return make_unique<Variable>(previous());

    if (match(Type::LEFT_PAREN)) {
        unique_ptr<Expr> expr = expression();
        consume(Type::RIGHT_PAREN, "Expected right paren `)` after expression");
        return make_unique<Grouping>(std::move(expr));
    }

    throw mash::ParseError("Expected expression", peek());
}

Token Parser::consume(Type expectedType, string errorMsg) {
    if (check(expectedType)) {
        return advance(); 
    }

    // Handle syntax error
    throw mash::ParseError(errorMsg, previous());
}

void Parser::synchronize() {
    advance();

    while (!isAtEnd()) {
        if (previous().type == Type::SEMICOLON) return;

        switch (peek().type) {
            case Type::INT:
            case Type::DOUBLE: 
            case Type::STRING_T:
            case Type::BOOLEAN:
            case Type::IF:
            case Type::FOR:
            case Type::WHILE:
            case Type::ECHO:
            case Type::EXEC:
                return;
                
            default:
                break;
        }

        advance();
    }
}

Token Parser::peek() {
    return tokens.at(current);
}

Token Parser::previous() {
    return tokens.at(current - 1);
}

Token Parser::advance() {
    if (!isAtEnd()) current++;
    return previous();
}

void Parser::retreat() {
    if (current > 0) current--;
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
