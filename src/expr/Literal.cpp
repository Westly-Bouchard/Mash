/**
 * @file Literal.cpp
 * @author Westly Bouchard (westly_bouchard@mines.edu)
 * @brief Implementation for literal AST nodes
 * @version 0.1
 * @date 2023-10-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "../../include/expr/Literal.h"

Literal::Literal(std::any value) {
    this->value = value;
}

std::any Literal::accept(ExprVisitor<std::any>& visitor) const {
    return visitor.visitLiteralExpr(*this);
}
