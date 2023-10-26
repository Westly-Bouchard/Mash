#ifndef EXPR_VISITOR_H
#define EXPR_VISITOR_H

class Binary;
class Grouping;
class Literal;
class Unary;
class Variable;

class ExprVisitor {
    public:
        virtual void visit(const Binary& expr) = 0;
        virtual void visit(const Grouping& expr) = 0;
        virtual void visit(const Literal& expr) = 0;
        virtual void visit(const Unary& expr) = 0;
        virtual void visit(const Variable& expr) = 0;
};

#endif