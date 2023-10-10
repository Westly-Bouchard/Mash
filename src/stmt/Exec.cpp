
#include "../../include/stmt/Exec.h"

Exec::Exec(Expr *toRun, Expr *result) {
    this->toRun = toRun;
    this->result = result;
}

std::any Exec::accept(StmtVisitor<std::any> *visitor) const {
    return visitor->visitExecStmt(this);
}