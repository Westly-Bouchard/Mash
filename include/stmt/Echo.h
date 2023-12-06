/**
 * @file Echo.h
 * @author Westly Bouchard (westly_bouchard@mines.edu)
 * @brief Base visitable AST node for echo statements
 * @version 0.1
 * @date 2023-10-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef ECHO_H
#define ECHO_H

#include <memory>

#include "../expr/Expr.h"
#include "Stmt.h"

class Echo : public Stmt {
public:
    std::unique_ptr<Expr> expr;

    Echo(std::unique_ptr<Expr> expr);

    void doAccept(StmtVisitorBase& visitor) override;
};

#endif
