#ifndef VAR_DECL_H
#define VAR_DECL_H

#include <memory>

#include "../expr/Expr.h"
#include "../Token.h"
#include "../TokenType.h"
#include "Stmt.h"

class VarDecl : public Stmt {
    private:
        TokenType::Type type;
        Token name;
        std::unique_ptr<Expr> expr;

    public:
        VarDecl(TokenType::Type type, Token name, std::unique_ptr<Expr> expr);

        std::any accept(StmtVisitor<std::any>& visitor) const override;
};

#endif