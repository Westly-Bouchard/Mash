/**
 * @file Grouping.h
 * @author Westly Bouchard (westly_bouchard@mines.edu)
 * @brief Visitable AST node for grouping expressions
 * @version 0.1
 * @date 2023-10-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef GROUPING_H
#define GROUPING_H

#include <memory>

#include "Expr.h"
#include "ExprVisitor.h"

class Grouping : public Expr {
    private:
        std::unique_ptr<Expr> expr;

    public:
        Grouping(std::unique_ptr<Expr> expr);

        std::any accept(ExprVisitor<std::any>& visitor) const override;
};

#endif