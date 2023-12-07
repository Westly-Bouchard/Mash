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

using namespace std;

// Token& Token::operator=(const Token& other) {
//     this->type = other.type;
//     this->lexeme = other.lexeme;
// }


string Token::asString() const {
    string result = TokenType::asStr(type) + " " + lexeme + " " + to_string(line);

    if (literal) {
        if (holds_alternative<int>(literal.value())) {
            result += get<int>(literal.value());
        } else if (holds_alternative<double>(literal.value())) {
            result += get<double>(literal.value());
        } else if (holds_alternative<string>(literal.value())) {
            result += get<string>(literal.value());
        } else if (holds_alternative<bool>(literal.value())) {
            result += get<bool>(literal.value());
        }
    }

    return result; 
}
