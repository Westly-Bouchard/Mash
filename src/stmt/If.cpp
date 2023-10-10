
#include "../../include/stmt/If.h"

If::If(Expr *condition, Stmt *thenBranch, Stmt *elseBranch) {
    this->condition = condition;
    this->thenBranch = thenBranch;
    this->elseBranch = elseBranch;
}

std::any If::accept(StmtVisitor<std::any> *visitor) const {
    return visitor->visitIfStmt(this);
}