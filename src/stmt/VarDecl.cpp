
#include "../../include/stmt/VarDecl.h"

VarDecl::VarDecl(TokenType::Type type, Token name, std::unique_ptr<Expr> expr) :
                   type(type), name(name), expr(std::move(expr)) {}

std::any VarDecl::accept(StmtVisitor<std::any>& visitor) const {
    return visitor.visitVarDeclStmt(*this);
}