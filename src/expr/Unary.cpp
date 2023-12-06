/**
 * @file Unary.cpp
 * @author Westly Bouchard (westly_bouchard@mines.edu)
 * @brief Implementation for unary AST nodes
 * @version 0.1
 * @date 2023-10-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "../../include/expr/Unary.h"

Unary::Unary(Token opp, std::unique_ptr<Expr> right) : opp(opp), right(std::move(right)) {}

void Unary::doAccept(ExprVisitorBase& visitor) const {
    visitor.visit(*this);
}
