#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <memory>

#include "../expr/Expr.h"
#include "Stmt.h"

class Expression : public Stmt {
    private:
        std::unique_ptr<Expr> expr;

    public:
        Expression(std::unique_ptr<Expr> expr);

        std::any accept(StmtVisitor<std::any>& visitor) const override;
};

#endif