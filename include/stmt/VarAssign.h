#ifndef VAR_ASSIGN_H
#define VAR_ASSIGN_H

#include <memory>

#include "../expr/Expr.h"
#include "Stmt.h"
#include "../Token.h"

class VarAssign : public Stmt {
    private:
        Token name;
        std::unique_ptr<Expr>expr;

    public:
        VarAssign(Token name, std::unique_ptr<Expr> expr);

        std::any accept(StmtVisitor<std::any>& visitor) const override;
};

#endif