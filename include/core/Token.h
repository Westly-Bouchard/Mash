/**
 * @file Token.h
 * @author Westly Bouchard (westly_bouchard@mines.edu)
 * @brief header for the Token type, used to store scanned source code
 * @version 0.1
 * @date 2023-10-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef TOKEN_H
#define TOKEN_H

#include <optional>
#include <string>
#include <variant>

#include "TokenType.h"

#define LITERAL_TYPE std::optional<std::variant<int, double, bool, std::string>>

class Token {
    public:
        TokenType::Type type;
        std::string lexeme;
        LITERAL_TYPE literal;
        int line;

        /**
         * @brief Construct a new Token object
         * 
         * @param type The type of the token
         * @param lexeme the lexeme that represents that token
         * @param literal the literal of the token if it has one
         * @param line the line that the token is located on in the source, for error reporting
         */
        Token(const TokenType::Type type, std::string lexeme, LITERAL_TYPE literal, const int line)
            : type(type) , lexeme(lexeme) , literal(literal), line(line) {}

        Token() : type(TokenType::MASH_EOF), literal(std::nullopt), line(0) {}

        // Token& operator=(const Token& other);

        /**
         * @brief For debugging and for easily representing a token as a string
         * 
         * @return string containing info about the token 
         */
        std::string asString() const;
};

#endif
