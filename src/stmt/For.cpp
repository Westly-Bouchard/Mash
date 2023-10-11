
#include "../../include/stmt/For.h"

For::For(std::unique_ptr<Expr> condition, std::unique_ptr<Stmt> stmt) :
          condition(std::move(condition)), stmt(std::move(stmt)) {}

std::any For::accept(StmtVisitor<std::any>& visitor) const {
    return visitor.visitForStmt(*this);
}