#ifndef WHILE_H
#define WHILE_H

#include "../expr/Expr.h"
#include "Stmt.h"

class While : public Stmt {
    private:
        Expr *condition;
        Stmt *stmt;

    public:
        While(Expr *condition, Stmt *stmt);

        std::any accept(StmtVisitor<std::any> *visitor) const override;
};

#endif