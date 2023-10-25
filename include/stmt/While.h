/**
 * @file While.h
 * @author Westly Bouchard (westly_bouchard@mines.edu)
 * @brief Visitable AST node for while statements
 * @version 0.1
 * @date 2023-10-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef WHILE_H
#define WHILE_H

#include <memory>

#include "../expr/Expr.h"
#include "Stmt.h"

class While : public Stmt {
    private:
        std::unique_ptr<Expr> condition;
        std::unique_ptr<Stmt> stmt;

    public:
        While(std::unique_ptr<Expr> condition, std::unique_ptr<Stmt> stmt);

        std::any accept(StmtVisitor<std::any>& visitor) const override;
};

#endif
