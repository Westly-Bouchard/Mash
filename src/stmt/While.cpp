
#include "../../include/stmt/While.h"

While::While(Expr *condition, Stmt *stmt) {
    this->condition = condition;
    this->stmt = stmt;
}

std::any While::accept(StmtVisitor<std::any> *visitor) const {
    return visitor->visitWhileStmt(this);
}