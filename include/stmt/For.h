#ifndef FOR_H
#define FOR_H

#include "../expr/Expr.h"
#include "Stmt.h"

class For : public Stmt {
    private:
        Expr *condition;
        Stmt *stmt;

    public:
        For(Expr *condition, Stmt *stmt);

        std::any accept(StmtVisitor<std::any> *visitor) const override;
};

#endif