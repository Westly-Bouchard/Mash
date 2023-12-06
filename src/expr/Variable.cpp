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

void Variable::doAccept(ExprVisitorBase& visitor) const {
    visitor.visit(*this);
}
