/**
 * @file Binary.cpp
 * @author Westly Bouchard (westly_bouchard@mines.edu)
 * @brief Implementation for binary AST nodes
 * @version 0.1
 * @date 2023-10-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "../../include/expr/Binary.h"

Binary::Binary(std::unique_ptr<Expr> left, Token opp, std::unique_ptr<Expr> right) : 
                left(std::move(left)), opp(opp), right(std::move(right)) {}

void Binary::doAccept(ExprVisitorBase& visitor) {
    visitor.visit(*this);
}

