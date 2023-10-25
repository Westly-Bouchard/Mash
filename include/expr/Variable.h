/**
 * @file Variable.h
 * @author Westly Bouchard (westly_bouchard@mines.edu)
 * @brief Visitable AST node for variable references
 * @version 0.1
 * @date 2023-10-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef MASH_VARIABLE_H
#define MASH_VARIABLE_H

#include "Expr.h"
#include "../core/Token.h"

class Variable : public Expr {
    private:
        Token name;

    public:
        Variable(Token name);

        std::any accept(ExprVisitor<std::any>& visitor) const override;
};

#endif
