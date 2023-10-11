
#include "../../include/expr/Grouping.h"

Grouping::Grouping(std::unique_ptr<Expr> expr) : expr(std::move(expr)) {}

std::any Grouping::accept(ExprVisitor<std::any>& visitor) const {
    return visitor.visitGroupingExpr(*this);
}