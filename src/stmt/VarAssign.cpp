
#include "../../include/stmt/VarAssign.h"

VarAssign::VarAssign(Token name, std::unique_ptr<Expr> expr) : name(name), expr(std::move(expr)) {}

std::any VarAssign::accept(StmtVisitor<std::any>& visitor) const {
    return visitor.visitVarAssignStmt(*this);
}