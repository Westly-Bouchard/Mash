/**
 * @file Variable.cpp
 * @author Westly Bouchard (westly_bouchard@mines.edu)
 * @brief Implementation for variable reference AST nodes
 * @version 0.1
 * @date 2023-10-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "../../include/expr/Variable.h"

Variable::Variable(Token name) : name(name) {}

std::any Variable::accept(ExprVisitor<std::any>& visitor) const {
    return visitor.visitVariableExpr(*this);
}
