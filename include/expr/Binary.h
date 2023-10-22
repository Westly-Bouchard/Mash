
#ifndef BINARY_H
#define BINARY_H

#include <memory>

#include "Expr.h"
#include "ExprVisitor.h"
#include "../core/Token.h"

class Binary : public Expr {
    private:
        std::unique_ptr<Expr> left;
        Token opp;
        std::unique_ptr<Expr> right;

    public:
        Binary(std::unique_ptr<Expr> left, Token opp, std::unique_ptr<Expr> right);

        std::any accept(ExprVisitor<std::any>& visitor) const override;
};

#endif