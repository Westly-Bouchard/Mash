/**
 * @file tokenType.h
 * @author Westly Bouchard (westly_bouchard@mines.edu)
 * @brief Enum for distinguishing types of tokens
 * @version 0.1
 * @date 2023-10-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef TOKEN_TYPE_H
#define TOKEN_TYPE_H

#include <string>
#include <unordered_map>

namespace TokenType {

    enum Type {
        // `(` and `)`
        LEFT_PAREN, RIGHT_PAREN,

        // `{` and `}`
        LEFT_BRACE, RIGHT_BRACE,

        // `,` and `;`
        COMMA, SEMICOLON,

        // Equality and boolean operators
        EQUAL, EQUAL_EQUAL, BANG, BANG_EQUAL,
        GREATER, GREATER_EQUAL,
        LESS, LESS_EQUAL,

        // Arithmetic operators
        PLUS, MINUS, SLASH, STAR,

        // Literals
        NUMBER_INT, NUMBER_DOUBLE, STRING, IDENTIFIER,

        // Reserved words
        TRUE, FALSE, IF, ELSE, FOR, WHILE, ECHO, EXEC,

        INT, DOUBLE, STRING_T, BOOLEAN,

        MASH_EOF
    };

    std::string asStr(Type type);

};

#endif