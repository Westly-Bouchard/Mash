/**
 * @file Grouping.cpp
 * @author Westly Bouchard (westly_bouchard@mines.edu)
 * @brief Implementation for grouping AST nodes
 * @version 0.1
 * @date 2023-10-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "../../include/expr/Grouping.h"

Grouping::Grouping(std::unique_ptr<Expr> expr) : expr(std::move(expr)) {}

void Grouping::accept(ExprVisitor& visitor) const {
    visitor.visit(*this);
}