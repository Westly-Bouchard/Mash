#ifndef STMT_VISITOR_H
#define STMT_VISITOR_H

class Block;
class Echo;
class Exec;
class Expression;
class For;
class If;
class VarAssign;
class VarDecl;
class While;

class StmtVisitor {
    public:
        virtual void visit(const Block& stmt) = 0;
        virtual void visit(const Echo& stmt) = 0;
        virtual void visit(const Exec& stmt) = 0;
        virtual void visit(const Expression& stmt) = 0;
        virtual void visit(const For& stmt) = 0;
        virtual void visit(const If& stmt) = 0;
        virtual void visit(const VarAssign& stmt) = 0;
        virtual void visit(const VarDecl& stmt) = 0;
        virtual void visit(const While& stmt) = 0;
};

#endif
