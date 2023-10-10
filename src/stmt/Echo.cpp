
#include "../../include/stmt/Echo.h"

Echo::Echo(Expr *expr) {
    this->expr = expr;
}

std::any Echo::accept(StmtVisitor<std::any> *visitor) const {
    return visitor->visitEchoStmt(this);
}