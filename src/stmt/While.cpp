/**
 * @file While.cpp
 * @author Westly Bouchard (westly_bouchard@mines.edu)
 * @brief Implementation for while AST nodes
 * @version 0.1
 * @date 2023-10-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "../../include/stmt/While.h"

While::While(std::unique_ptr<Expr> condition, std::unique_ptr<Stmt> stmt) :
              condition(std::move(condition)), stmt(std::move(stmt)) {}

void While::accept(StmtVisitor& visitor) const {
    visitor.visit(*this);
}
