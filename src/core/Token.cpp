/**
 * @file Token.cpp
 * @author Westly Bouchard (westly_bouchard@mines.edu)
 * @brief implementation for token type
 * @version 0.1
 * @date 2023-10-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <cstring>

#include "../../include/core/Token.h"

string Token::asString() {
    string result = TokenType::asStr(type) + " " + lexeme + " " + to_string(line);

    

    if (strcmp(literal.type().name(), "int") == 0) {
        result += any_cast<int>(literal);
    } else if (strcmp(literal.type().name(), "string") == 0) {
        result += any_cast<string>(literal);
    } else if (strcmp(literal.type().name(), "bool") == 0) {
        result += any_cast<bool>(literal);
    }

    return result; 
}