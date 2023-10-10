#ifndef VAR_DECL_H
#define VAR_DECL_H

#include "../expr/Expr.h"
#include "../Token.h"
#include "Stmt.h"

class VarDecl : public Stmt {
    private:
        Token *type;
        Token *name;
        Expr *expr;

    public:
        VarDecl(Token *type, Token *name, Expr *expr);

        std::any accept(StmtVisitor<std::any> *visitor) const override;
};

#endif