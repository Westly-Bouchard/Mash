#ifndef ECHO_H
#define ECHO_H

#include <memory>

#include "../expr/Expr.h"
#include "Stmt.h"

class Echo : public Stmt {
    private:
        std::unique_ptr<Expr> expr;

    public:
        Echo(std::unique_ptr<Expr> expr);

        std::any accept(StmtVisitor<std::any>& visitor) const override;
};

#endif