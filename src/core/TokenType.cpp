/**
 * @file TokenType.cpp
 * @author Westly Bouchard (westly_bouchard@mines.edu)
 * @brief Implementation of the token type enum and it's mapping to string
 * @version 0.1
 * @date 2023-10-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "../../include/core/TokenType.h"

std::unordered_map<int, std::string> mapping = {
    {0, "Left Paren"}, {1, "Right Paren"},

    {2, "Left Brace"}, {3, "Right Brace"},

    {4, "Comma"}, {5, "Semicolon"},

    {6, "Equal"}, {7, "Double Equal"}, {8, "Bang"}, {9, "Bang Equal"},
    {10, "Greater"}, {11, "Greater Equal"}, 
    {12, "Less"}, {13, "Less Equal"},

    {14, "Plus"}, {15, "Minus"}, {16, "Slash"}, {17, "Star"},

    {18, "Integer Literal"}, {19, "Floating Point Literal"}, {20, "String literal"}, {21, "Identifier"},

    {22, "True"}, {23, "False"}, {24, "If"}, {25, "Else"}, {26, "For"}, {27, "While"}, {28, "Echo"},
    {29, "Exec"},

    {30, "TypeDecl int"}, {31, "TypeDecl double"}, {32, "TypeDecl string"}, {33, "TypeDecl boolean"},

    {34, "End of File"}
 };

std::string TokenType::asStr(TokenType::Type type) {
    return mapping.at(type);
}
