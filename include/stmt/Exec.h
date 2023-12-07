/**
 * @file Exec.h
 * @author Westly Bouchard (westly_bouchard@mines.edu)
 * @brief Visitable AST node for exec statements
 * @version 0.1
 * @date 2023-10-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef EXEC_H
#define EXEC_H

#include <memory>

#include "../expr/Expr.h"
#include "../core/Token.h"
#include "Stmt.h"

class Exec : public Stmt {
public:
    std::unique_ptr<Expr> toRun;
    Token result;

    Exec(std::unique_ptr<Expr> toRun, Token result);

    void doAccept(StmtVisitorBase& visitor) override;
};

#endif
