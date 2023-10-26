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

class Grouping : public Expr {
    public:
        std::unique_ptr<Expr> expr;

        Grouping(std::unique_ptr<Expr> expr);

        void accept(ExprVisitor& visitor) const override;
};

#endif
