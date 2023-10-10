
#include "../../include/expr/Literal.h"

Literal::Literal(std::any value) {
    this->value = value;
}

std::any Literal::accept(ExprVisitor<std::any> *visitor) const {
    return visitor->visitLiteralExpr(this);
}