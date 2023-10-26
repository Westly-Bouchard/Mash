/**
 * @file ExprVisitor.h
 * @author Westly Bouchard (westly_bouchard@mines.edu)
 * @brief Base visitor for expressions
 * @version 0.1
 * @date 2023-10-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */

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
