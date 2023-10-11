
#include "../../include/stmt/Echo.h"

Echo::Echo(std::unique_ptr<Expr> expr) : expr(std::move(expr)) {}

std::any Echo::accept(StmtVisitor<std::any>& visitor) const {
    return visitor.visitEchoStmt(*this);
}