
#include "../../include/stmt/Expression.h"

Expression::Expression(Expr *expr) {
    this->expr = expr;
}

std::any Expression::accept(StmtVisitor<std::any> *visitor) const {
    return visitor->visitExpressionStmt(this);
}