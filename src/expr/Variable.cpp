
#include "../../include/expr/Variable.h"

Variable::Variable(Token name) : name(name) {}

std::any Variable::accept(ExprVisitor<std::any>& visitor) const {
    return visitor.visitVariableExpr(*this);
}