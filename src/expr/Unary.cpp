
#include "../../include/expr/Unary.h"

Unary::Unary(Token *opp, Expr *right) {
    this->opp = opp;
    this->right = right;
}

std::any Unary::accept(ExprVisitor<std::any> *visitor) const {
    return visitor->visitUnaryExpr(this);
}