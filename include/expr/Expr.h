/**
 * @file Expr.h
 * @author Westly Bouchard (westly_bouchard@mines.edu)
 * @brief Base visitable class for expression AST nodes
 * @version 0.1
 * @date 2023-10-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef EXPR_H
#define EXPR_H

#include "ExprVisitor.h"

class Stmt;

class Expr {
public:
    virtual ~Expr() = default;

    template <typename T>
    T accept(ExprVisitor<T>& visitor) const {
        doAccept(visitor);
        return visitor.result;
    }

    virtual void doAccept(ExprVisitorBase& visitor) const = 0;
};

#endif
