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