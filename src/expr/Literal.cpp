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

Literal::Literal(LITERAL_TYPE value) : value(value) {}

void Literal::doAccept(ExprVisitorBase& visitor) const {
    visitor.visit(*this);
}
