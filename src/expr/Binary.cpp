
#include "../../include/expr/Binary.h"

Binary::Binary(Expr *left, Token *opp, Expr *right) {
    this->left = left;
    this->opp = opp;
    this->right = right;
}

std::any Binary::accept(ExprVisitor<std::any> *visitor) const {
    return visitor->visitBinaryExpr(this);
}