#ifndef FOR_H
#define FOR_H

#include <memory>

#include "../expr/Expr.h"
#include "Stmt.h"

class For : public Stmt {
    private:
        std::unique_ptr<Expr> condition;
        std::unique_ptr<Stmt> stmt;

    public:
        For(std::unique_ptr<Expr> condition, std::unique_ptr<Stmt> stmt);

        std::any accept(StmtVisitor<std::any>& visitor) const override;
};

#endif