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
#include "../core/TokenType.h"

class Literal : public Expr {
    public:
        std::any value;

        TokenType::Type type;

        Literal(std::any value, TokenType::Type type);

        void accept(ExprVisitor& visitor) const override;
};

#endif
