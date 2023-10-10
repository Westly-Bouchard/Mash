#ifndef GROUPING_H
#define GROUPING_H

#include "Expr.h"
#include "ExprVisitor.h"

class Grouping : public Expr {
    private:
        Expr *expression;

    public:
        Grouping(Expr *expression);

        std::any accept(ExprVisitor<std::any> *visitor) const override;
};

#endif