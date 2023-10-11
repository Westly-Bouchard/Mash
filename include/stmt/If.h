#ifndef IF_H
#define IF_H

#include <memory>

#include "../expr/Expr.h"
#include "Stmt.h"

class If : public Stmt {
    private:
        std::unique_ptr<Expr> condition;
        std::unique_ptr<Stmt> thenBranch;
        std::unique_ptr<Stmt> elseBranch;

    public:
        If(
            std::unique_ptr<Expr> condition,
            std::unique_ptr<Stmt> thenBranch,
            std::unique_ptr<Stmt> elseBranch
        );

        std::any accept(StmtVisitor<std::any>& visitor) const override;
};

#endif