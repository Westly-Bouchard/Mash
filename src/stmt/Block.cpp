
#include "../../include/stmt/Block.h"

Block::Block(std::vector<std::unique_ptr<Stmt>> statements) : statements(std::move(statements)) {}

std::any Block::accept(StmtVisitor<std::any>& visitor) const {
    return visitor.visitBlockStmt(*this);
}