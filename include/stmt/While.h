#ifndef WHILE_H
#define WHILE_H

#include <memory>

#include "../expr/Expr.h"
#include "Stmt.h"

class While : public Stmt {
    private:
        std::unique_ptr<Expr> condition;
        std::unique_ptr<Stmt> stmt;

    public:
        While(std::unique_ptr<Expr> condition, std::unique_ptr<Stmt> stmt);

        std::any accept(StmtVisitor<std::any>& visitor) const override;
};

#endif