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

#include <memory>

#include "Expr.h"
#include "../core/Token.h"

class Unary : public Expr {
public:
    Token opp;
    std::unique_ptr<Expr> right;

    Unary(Token opp, std::unique_ptr<Expr> right);

    void doAccept(ExprVisitorBase& visitor) override;
};

#endif
