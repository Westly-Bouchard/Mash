
#include "../../include/stmt/While.h"

While::While(std::unique_ptr<Expr> condition, std::unique_ptr<Stmt> stmt) :
              condition(std::move(condition)), stmt(std::move(stmt)) {}

std::any While::accept(StmtVisitor<std::any>& visitor) const {
    return visitor.visitWhileStmt(*this);
}