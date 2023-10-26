/**
 * @file Expression.cpp
 * @author Westly Bouchard (westly_bouchard@mines.edu)
 * @brief Implementation for expression statement AST nodes
 * @version 0.1
 * @date 2023-10-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "../../include/stmt/Expression.h"

Expression::Expression(std::unique_ptr<Expr> expr) : expr(std::move(expr)) {}

void Expression::accept(StmtVisitor& visitor) const {
    visitor.visit(*this);
}
