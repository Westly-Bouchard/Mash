/**
 * @file StmtVisitor.h
 * @author Westly Bouchard (westly_bouchard@mines.edu)
 * @brief Base visitor for statements
 * @version 0.1
 * @date 2023-10-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef STMT_VISITOR_H
#define STMT_VISITOR_H

// Define classes here to prevent circular inclusion
class Block;
class Echo;
class Exec;
class Expression;
class For;
class If;
class VarAssign;
class VarDecl;
class While;

class StmtVisitorBase {
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

    virtual ~StmtVisitorBase() = default;
};

template <typename T>
class StmtVisitor : public StmtVisitorBase {
public:
    T result;
};

#endif
