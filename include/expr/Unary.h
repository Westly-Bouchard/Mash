/**
 * @file Unary.h
 * @author Westly Bouchard (westly_bouchard@mines.edu)
 * @brief Visitable AST node for unary expressions
 * @version 0.1
 * @date 2023-10-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef UNARY_H
#define UNARY_H

#include <any>
#include <memory>

#include "Expr.h"
#include "ExprVisitor.h"
#include "../core/Token.h"

class Unary : public Expr {
    private:
        Token opp;
        std::unique_ptr<Expr> right;

    public:
        Unary(Token opp, std::unique_ptr<Expr> right);

        std::any accept(ExprVisitor<std::any>& visitor) const override;
};

#endif
