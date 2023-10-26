/**
 * @file Exec.cpp
 * @author Westly Bouchard (westly_bouchard@mines.edu)
 * @brief Implementation for exec AST nodes
 * @version 0.1
 * @date 2023-10-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "../../include/stmt/Exec.h"

Exec::Exec(std::unique_ptr<Expr> toRun, std::unique_ptr<Expr> result) :
            toRun(std::move(toRun)), result(std::move(result)) {}

void Exec::accept(StmtVisitor& visitor) const {
    visitor.visit(*this);
}
