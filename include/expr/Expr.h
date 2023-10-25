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

#include <any>

#include "ExprVisitor.h"

class Expr {
    public:
        virtual std::any accept(ExprVisitor<std::any>& visitor) const = 0;

        virtual ~Expr() = default;
};

#endif