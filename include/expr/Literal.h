/**
 * @file Literal.h
 * @author Westly Bouchard (westly_bouchard@mines.edu)
 * @brief Visitable AST node for literal expressions
 * @version 0.1
 * @date 2023-10-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef LITERAL_H
#define LITERAL_H

#include <any>

#include "Expr.h"
#include "ExprVisitor.h"

class Literal : public Expr {
    private:
        std::any value;

    public:
        Literal(std::any value);

        std::any accept(ExprVisitor<std::any>& visitor) const override;
};

#endif