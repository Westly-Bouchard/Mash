
#include "../../include/expr/Binary.h"

Binary::Binary(std::unique_ptr<Expr> left, Token opp, std::unique_ptr<Expr> right) : 
                left(std::move(left)), opp(opp), right(std::move(right)) {}

std::any Binary::accept(ExprVisitor<std::any>& visitor) const {
    return visitor.visitBinaryExpr(*this);
}