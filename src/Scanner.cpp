/**
 * @file scanner.cpp
 * @author Westly Bouchard
 * @brief implementations for the Tokenizer component of the interpreter
 * @version 0.1
 * @date 2023-10-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <iostream>

#include "../include/Scanner.h"
#include "../include/TokenType.h"

using namespace TokenType;

Scanner::Scanner(std::ifstream& source) : source(source) {
    // tokens = {};
}

std::map<std::string, Type> Scanner::keywords = {
    {"true", TRUE},
    {"false", FALSE},
    {"if", IF},
    {"else", ELSE},
    {"for", FOR},
    {"while", WHILE},
    {"echo", ECHO},
    {"exec", EXEC},
    {"int", INT},
    {"double", DOUBLE},
    {"string", STRING_T},
    {"boolean", BOOLEAN},
};

std::vector<Token>* Scanner::scanTokens() {

    int line = 1;

    char c;

    while (source.peek() != EOF) {

        c = advance();

        switch (c) {


            // Ignore whitespace
            case ' ':
            case '\t':
            case '\r':
                break;

            case '\n':
                line++;
                break;


            // Single Character tokens
            case '(':
                tokens.push_back(Token(Type::LEFT_PAREN, "(", nullptr, line));
                break;

            case ')':
                tokens.push_back(Token(Type::RIGHT_PAREN, ")", nullptr, line));
                break;

            case '{':
                tokens.push_back(Token(Type::LEFT_BRACE, "{", nullptr, line));
                break;

            case '}':
                tokens.push_back(Token(Type::RIGHT_BRACE, "}", nullptr, line));
                break;

            case ',':
                tokens.push_back(Token(Type::COMMA, ",", nullptr, line));
                break;

            case ';':
                tokens.push_back(Token(Type::SEMICOLON, ";", nullptr, line));
                break;

            case '+':
                tokens.push_back(Token(Type::PLUS, "+", nullptr, line));
                break;

            case '-':
                tokens.push_back(Token(Type::MINUS, "-", nullptr, line));
                break;

            case '*':
                tokens.push_back(Token(Type::STAR, "*", nullptr, line));
                break;

            // Comments and or just the slash
            case '/': {
                // Single line comments
                if (source.peek() == '/') {
                    while (source.peek() != '\n' && !source.eof()) advance();
                } else if (source.peek() == '*') {
                    advance();
                    while (source.peek() != '*' && peekNext() != '/' && !source.eof()) {
                        c = advance();
                        if (c == '\n') line++;
                    }
                    // Consume the `*/` characters at the end of the comment
                    advance();
                    advance();
                } else {
                    tokens.push_back(Token(Type::SLASH, "/", nullptr, line));
                }
                break;
            }
            
            // Equal or double equal signs
            case '=': {
                if (source.peek() == '=') {
                    tokens.push_back(Token(Type::EQUAL_EQUAL, "==", nullptr, line));
                    advance();
                } else {
                    tokens.push_back(Token(Type::EQUAL, "=", nullptr, line));
                }
                break;
            }

            // Bang or bang equals
            case '!': {
                if (source.peek() == '=') {
                    tokens.push_back(Token(Type::BANG_EQUAL, "!=", nullptr, line));
                    advance();
                } else {
                    tokens.push_back(Token(Type::BANG, "=", nullptr, line));
                }
                break;
            }

            // Greater than and less than
            case '>': {
                if (source.peek() == '=') {
                    tokens.push_back(Token(Type::GREATER_EQUAL, ">=", nullptr, line));
                    advance();
                } else {
                    tokens.push_back(Token(Type::GREATER, "=", nullptr, line));
                }
                break;
            }

            case '<': {
                if (source.peek() == '=') {
                    tokens.push_back(Token(Type::LESS_EQUAL, "<=", nullptr, line));
                    advance();
                } else {
                    tokens.push_back(Token(Type::LESS, "=", nullptr, line));
                }
                break;
            }

            // String literals
            case '"': {
                string literal = "";
                while (source.peek() != '"' && !source.eof()) {
                    if (source.peek() == '\n') line++;
                    literal.push_back(advance());
                }

                if (source.eof()) {
                    cerr << "Encountered error: Unterminated string literal on line: " << line;
                    return nullptr;
                }

                // Consume closing quotes
                advance();
                string text = "\"" + literal + "\"";
                tokens.push_back(Token(Type::STRING, text, literal, line));
                break;
            }

            default:
                // First thing we'll check is if it's a number literal
                string lexeme;
                if (isdigit(c)) {
                    lexeme.push_back(c);
                    while (isdigit(source.peek())) lexeme.push_back(advance());

                    if (source.peek() == '.') {
                        lexeme.push_back(advance());
                        while (isdigit(source.peek())) lexeme.push_back(advance());
                        tokens.push_back(Token(Type::NUMBER_DOUBLE, lexeme, std::stod(lexeme), line));
                    } else {
                        tokens.push_back(Token(Type::NUMBER_INT, lexeme, std::stoi(lexeme), line));
                    }
                }

                if (isalpha(c)) {
                    // Look for a keyword 
                    lexeme.push_back(c);
                    while (iswalnum(source.peek())) lexeme.push_back(advance());

                    if (keywords.find(lexeme) == keywords.end()) {
                        // If the lexeme is not in the keywords, we assume it's an identifier
                        tokens.push_back(Token(Type::IDENTIFIER, lexeme, nullptr, line));
                    } else {
                        tokens.push_back(Token(keywords.at(lexeme), lexeme, nullptr, line));
                    }
                }
        }
    }

    tokens.push_back(Token(Type::MASH_EOF, "", nullptr, line));

    return &tokens; 
}

char Scanner::peekNext() {
    char temp;
    source.get(temp);
    temp = source.peek();
    source.unget();
    return temp;
}

char Scanner::advance() {
    char temp;
    source.get(temp);
    return temp;
}