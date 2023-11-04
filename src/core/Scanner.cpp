/**
 * @file scanner.cpp
 * @author Westly Bouchard (westly_bouchard@mines.edu)
 * @brief implementations for the Tokenizer component of the interpreter
 * @version 0.1
 * @date 2023-10-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <iostream>

#include "../../include/core/Scanner.h"
#include "../../include/core/TokenType.h"

#include "../../include/tool/Error.hpp"

using namespace TokenType;
using namespace std;

Scanner::Scanner(ifstream& source) : source(source) {}

map<string, Type> Scanner::keywords = {
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

vector<Token>* Scanner::scanTokens() {

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
                tokens.push_back(Token(Type::LEFT_PAREN, "(", nullopt, line));
                break;

            case ')':
                tokens.push_back(Token(Type::RIGHT_PAREN, ")", nullopt, line));
                break;

            case '{':
                tokens.push_back(Token(Type::LEFT_BRACE, "{", nullopt, line));
                break;

            case '}':
                tokens.push_back(Token(Type::RIGHT_BRACE, "}", nullopt, line));
                break;

            case ',':
                tokens.push_back(Token(Type::COMMA, ",", nullopt, line));
                break;

            case ';':
                tokens.push_back(Token(Type::SEMICOLON, ";", nullopt, line));
                break;

            case '+':
                tokens.push_back(Token(Type::PLUS, "+", nullopt, line));
                break;

            case '-':
                tokens.push_back(Token(Type::MINUS, "-", nullopt, line));
                break;

            case '*':
                tokens.push_back(Token(Type::STAR, "*", nullopt, line));
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
                    tokens.push_back(Token(Type::SLASH, "/", nullopt, line));
                }
                break;
            }
            
            // Equal or double equal signs
            case '=': {
                if (source.peek() == '=') {
                    tokens.push_back(Token(Type::EQUAL_EQUAL, "==", nullopt, line));
                    advance();
                } else {
                    tokens.push_back(Token(Type::EQUAL, "=", nullopt, line));
                }
                break;
            }

            // Bang or bang equals
            case '!': {
                if (source.peek() == '=') {
                    tokens.push_back(Token(Type::BANG_EQUAL, "!=", nullopt, line));
                    advance();
                } else {
                    tokens.push_back(Token(Type::BANG, "!", nullopt, line));
                }
                break;
            }

            // Greater than and less than
            case '>': {
                if (source.peek() == '=') {
                    tokens.push_back(Token(Type::GREATER_EQUAL, ">=", nullopt, line));
                    advance();
                } else {
                    tokens.push_back(Token(Type::GREATER, ">", nullopt, line));
                }
                break;
            }

            case '<': {
                if (source.peek() == '=') {
                    tokens.push_back(Token(Type::LESS_EQUAL, "<=", nullopt, line));
                    advance();
                } else {
                    tokens.push_back(Token(Type::LESS, "<", nullopt, line));
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
                    throw mash::LexError("Unterminated string literal", line);
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
                        tokens.push_back(Token(Type::NUMBER_DOUBLE, lexeme, stod(lexeme), line));
                    } else {
                        tokens.push_back(Token(Type::NUMBER_INT, lexeme, stoi(lexeme), line));
                    }
                } else if (isalpha(c)) {
                    // Look for a keyword 
                    lexeme.push_back(c);
                    while (iswalnum(source.peek())) lexeme.push_back(advance());

                    if (keywords.find(lexeme) == keywords.end()) {
                        // If the lexeme is not in the keywords, we assume it's an identifier
                        tokens.push_back(Token(Type::IDENTIFIER, lexeme, nullopt, line));
                    } else {
                        tokens.push_back(Token(keywords.at(lexeme), lexeme, nullopt, line));
                    }
                } else {
                    throw mash::LexError("Unexpected character on line ", line);
                }
        }
    }

    tokens.push_back(Token(Type::MASH_EOF, "", nullopt, line));

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
