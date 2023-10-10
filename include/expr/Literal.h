#ifndef LITERAL_H
#define LITERAL_H

#include <any>

#include "Expr.h"
#include "ExprVisitor.h"

class Literal : public Expr {
    private:
        std::any value;

    public:
        Literal(std::any value);

        std::any accept(ExprVisitor<std::any> *visitor) const override;
};

#endif