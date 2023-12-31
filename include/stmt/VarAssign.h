/**
 * @file VarAssign.h
 * @author Westly Bouchard (westly_bouchard@mines.edu)
 * @brief Visitable AST node for variable assignment expressions
 * @version 0.1
 * @date 2023-10-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef VAR_ASSIGN_H
#define VAR_ASSIGN_H

#include <memory>

#include "../expr/Expr.h"
#include "Stmt.h"
#include "../core/Token.h"

class VarAssign : public Stmt {
public:
    Token name;
    std::unique_ptr<Expr>expr;

    VarAssign(Token name, std::unique_ptr<Expr> expr);

    void doAccept(StmtVisitorBase& visitor) override;
};

#endif
