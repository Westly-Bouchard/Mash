#ifndef ECHO_H
#define ECHO_H

#include "../expr/Expr.h"
#include "Stmt.h"

class Echo : public Stmt {
    private:
        Expr *expr;

    public:
        Echo(Expr *expr);

        std::any accept(StmtVisitor<std::any> *visitor) const override;
};

#endif