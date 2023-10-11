
#include "../../include/stmt/If.h"

If::If(
        std::unique_ptr<Expr> condition,
        std::unique_ptr<Stmt> thenBranch,
        std::unique_ptr<Stmt> elseBranch
    ) : 
        condition(std::move(condition)),
        thenBranch(std::move(thenBranch)),
        elseBranch(std::move(elseBranch)) {}

std::any If::accept(StmtVisitor<std::any>& visitor) const {
    return visitor.visitIfStmt(*this);
}