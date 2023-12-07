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

#include <utility>

#include "../../include/stmt/Exec.h"

Exec::Exec(std::unique_ptr<Expr> toRun, Token result) :
            toRun(std::move(toRun)), result(std::move(result)) {}

void Exec::doAccept(StmtVisitorBase& visitor) {
    visitor.visit(*this);
}
