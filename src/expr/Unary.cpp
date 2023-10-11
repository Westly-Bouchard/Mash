
#include "../../include/expr/Unary.h"

Unary::Unary(Token opp, std::unique_ptr<Expr> right) : opp(opp), right(std::move(right)) {}

std::any Unary::accept(ExprVisitor<std::any>& visitor) const {
    return visitor.visitUnaryExpr(*this);
}