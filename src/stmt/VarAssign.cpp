/**
 * @file VarAssign.cpp
 * @author Westly Bouchard (westly_bouchard@mines.edu)
 * @brief Implementation for variable assignment AST nodes
 * @version 0.1
 * @date 2023-10-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "../../include/stmt/VarAssign.h"

VarAssign::VarAssign(Token name, std::unique_ptr<Expr> expr) : name(name), expr(std::move(expr)) {}

void VarAssign::accept(StmtVisitor& visitor) const {
    visitor.visit(*this);
}
