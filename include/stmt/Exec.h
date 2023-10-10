#ifndef EXEC_H
#define EXEC_H

#include "../expr/Expr.h"
#include "Stmt.h"

class Exec : public Stmt {
    private:
        Expr *toRun;
        Expr *result;

    public:
        Exec(Expr *toRun, Expr *result);

        std::any accept(StmtVisitor<std::any> *visitor) const override;
};

#endif