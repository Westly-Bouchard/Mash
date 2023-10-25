/**
 * @file If.h
 * @author Westly Bouchard (westly_bouchard@mines.edu)
 * @brief Visitable AST node for if statements
 * @version 0.1
 * @date 2023-10-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef IF_H
#define IF_H

#include <memory>

#include "../expr/Expr.h"
#include "Stmt.h"

class If : public Stmt {
    private:
        std::unique_ptr<Expr> condition;
        std::unique_ptr<Stmt> thenBranch;
        std::unique_ptr<Stmt> elseBranch;

    public:
        If(
            std::unique_ptr<Expr> condition,
            std::unique_ptr<Stmt> thenBranch,
            std::unique_ptr<Stmt> elseBranch
        );

        std::any accept(StmtVisitor<std::any>& visitor) const override;
};

#endif