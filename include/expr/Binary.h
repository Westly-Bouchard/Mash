
#ifndef BINARY_H
#define BINARY_H

#include "Expr.h"
#include "ExprVisitor.h"
#include "../Token.h"

class Binary : public Expr {
    private:
        Expr *left;
        Token *opp;
        Expr *right;

    public:
        Binary(Expr *left, Token *opp, Expr *right);

        std::any accept(ExprVisitor<std::any> *visitor) const override;
};

#endif