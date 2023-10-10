
#include "../../include/stmt/VarDecl.h"

VarDecl::VarDecl(Token *type, Token *name, Expr *expr) {
    this->type = type;
    this->name = name;
    this->expr = expr;
}

std::any VarDecl::accept(StmtVisitor<std::any> *visitor) const {
    return visitor->visitVarDeclStmt(this);
}