
#include "../../include/expr/Grouping.h"

Grouping::Grouping(Expr *expression) {
    this->expression = expression;
}

std::any Grouping::accept(ExprVisitor<std::any> *visitor) const {
    return visitor->visitGroupingExpr(this);
}