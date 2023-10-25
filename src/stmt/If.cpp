/**
 * @file If.cpp
 * @author Westly Bouchard (westly_bouchard@mines.edu)
 * @brief Implementation for if AST nodes
 * @version 0.1
 * @date 2023-10-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "../../include/stmt/If.h"

If::If(
        std::unique_ptr<Expr> condition,
        std::unique_ptr<Stmt> thenBranch,
        std::unique_ptr<Stmt> elseBranch
    ) : 
        condition(std::move(condition)),
        thenBranch(std::move(thenBranch)),
        elseBranch(std::move(elseBranch)) {}

std::any If::accept(StmtVisitor<std::any>& visitor) const {
    return visitor.visitIfStmt(*this);
}
