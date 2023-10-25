/**
 * @file Binary.h
 * @author Westly Bouchard (westly_bouchard@mines.edu)
 * @brief Visitable AST node for binary expressions
 * @version 0.1
 * @date 2023-10-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef BINARY_H
#define BINARY_H

#include <memory>

#include "Expr.h"
#include "../core/Token.h"

class Binary : public Expr {
    private:
        std::unique_ptr<Expr> left;
        Token opp;
        std::unique_ptr<Expr> right;

    public:
        Binary(std::unique_ptr<Expr> left, Token opp, std::unique_ptr<Expr> right);
};

#endif
