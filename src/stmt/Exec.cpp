
#include "../../include/stmt/Exec.h"

Exec::Exec(std::unique_ptr<Expr> toRun, std::unique_ptr<Expr> result) :
            toRun(std::move(toRun)), result(std::move(result)) {}

std::any Exec::accept(StmtVisitor<std::any>& visitor) const {
    return visitor.visitExecStmt(*this);
}