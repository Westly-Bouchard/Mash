#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "../expr/Expr.h"
#include "Stmt.h"

class Expression : public Stmt {
    private:
        Expr *expr;

    public:
        Expression(Expr *expr);

        std::any accept(StmtVisitor<std::any> *visitor) const override;
};

#endif