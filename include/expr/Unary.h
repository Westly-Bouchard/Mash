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