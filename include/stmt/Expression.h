/**
 * @file Expression.h
 * @author Westly Bouchard (westly_bouchard@mines.edu)
 * @brief Visitable AST node for expression statements
 * @version 0.1
 * @date 2023-10-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <memory>

#include "../expr/Expr.h"
#include "Stmt.h"

class Expression : public Stmt {
    public:
        std::unique_ptr<Expr> expr;

        Expression(std::unique_ptr<Expr> expr);

        void accept(StmtVisitor& visitor) const override;
};

#endif
