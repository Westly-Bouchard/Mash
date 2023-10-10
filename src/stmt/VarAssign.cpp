
#include "../../include/stmt/VarAssign.h"

VarAssign::VarAssign(Token *name, Expr *expr) {
    this->name = name;
    this->expr = expr;
}

std::any VarAssign::accept(StmtVisitor<std::any> *visitor) const {
    return visitor->visitVarAssignStmt(this);
}