#ifndef EXEC_H
#define EXEC_H

#include <memory>

#include "../expr/Expr.h"
#include "Stmt.h"

class Exec : public Stmt {
    private:
        std::unique_ptr<Expr> toRun;
        std::unique_ptr<Expr> result;

    public:
        Exec(std::unique_ptr<Expr> toRun, std::unique_ptr<Expr> result);

        std::any accept(StmtVisitor<std::any>& visitor) const override;
};

#endif