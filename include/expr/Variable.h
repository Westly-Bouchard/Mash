#ifndef MASH_VARIABLE_H
#define MASH_VARIABLE_H

#include "Expr.h"
#include "../Token.h"

class Variable : public Expr {
    private:
        Token name;

    public:
        Variable(Token name);

        std::any accept(ExprVisitor<std::any>& visitor) const override;
};

#endif