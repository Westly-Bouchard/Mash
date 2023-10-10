
#include "../../include/stmt/Block.h"

Block::Block(std::vector<Stmt*> statements) {
    this->statements = statements;
}

std::any Block::accept(StmtVisitor<std::any> *visitor) const {
    return visitor->visitBlockStmt(this);
}