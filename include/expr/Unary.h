#ifndef UNARY_H
#define UNARY_H

#include <any>

#include "Expr.h"
#include "ExprVisitor.h"
#include "../Token.h"

class Unary : public Expr {
    private:
        Token *opp;
        Expr *right;

    public:
        Unary(Token *opp, Expr *right);

        std::any accept(ExprVisitor<std::any> *visitor) const override;
};

#endif