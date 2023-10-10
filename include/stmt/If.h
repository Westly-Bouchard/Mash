#ifndef IF_H
#define IF_H

#include "../expr/Expr.h"
#include "Stmt.h"

class If : public Stmt {
    private:
        Expr *condition;
        Stmt *thenBranch;
        Stmt *elseBranch;

    public:
        If(Expr *condition, Stmt *thenBranch, Stmt *elseBranch);

        std::any accept(StmtVisitor<std::any> *visitor) const override;
};

#endif