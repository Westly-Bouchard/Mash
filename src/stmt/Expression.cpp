
#include "../../include/stmt/Expression.h"

Expression::Expression(std::unique_ptr<Expr> expr) : expr(std::move(expr)) {}

std::any Expression::accept(StmtVisitor<std::any>& visitor) const {
    return visitor.visitExpressionStmt(*this);
}