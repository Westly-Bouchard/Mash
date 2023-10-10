
#include "../../include/stmt/For.h"

For::For(Expr *condition, Stmt *stmt) {
    this->condition = condition;
    this->stmt = stmt;
}

std::any For::accept(StmtVisitor<std::any> *visitor) const {
    return visitor->visitForStmt(this);
}