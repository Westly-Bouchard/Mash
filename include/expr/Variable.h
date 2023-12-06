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
public:
    Token name;

    Variable(Token name);

    void doAccept(ExprVisitorBase& visitor) const override;
};

#endif
