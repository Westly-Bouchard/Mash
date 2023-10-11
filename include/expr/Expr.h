

#ifndef EXPR_H
#define EXPR_H

#include <any>

#include "ExprVisitor.h"

class Expr {
    public:
        virtual std::any accept(ExprVisitor<std::any>& visitor) const = 0;

        virtual ~Expr() = default;
};

#endif