#ifndef VAR_ASSIGN_H
#define VAR_ASSIGN_H

#include "../expr/Expr.h"
#include "Stmt.h"
#include "../Token.h"

class VarAssign : public Stmt {
    private:
        Token *name;
        Expr *expr;

    public:
        VarAssign(Token *name, Expr *expr);

        std::any accept(StmtVisitor<std::any> *visitor) const override;
};

#endif