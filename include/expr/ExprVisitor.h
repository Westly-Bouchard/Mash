#ifndef EXPR_VISITOR_H
#define EXPR_VISITOR_H

class Binary;
class Grouping;
class Literal;
class Unary;
class Variable;

template <typename R>
class ExprVisitor {
    public:
        virtual R visitBinaryExpr(const Binary& binaryExpr) = 0;
        virtual R visitGroupingExpr(const Grouping& groupingExpr) = 0; 
        virtual R visitLiteralExpr(const Literal& literalExpr) = 0;
        virtual R visitUnaryExpr(const Unary& unaryExpr) = 0;
        virtual R visitVariableExpr(const Variable& variableExpr) = 0;
};

#endif