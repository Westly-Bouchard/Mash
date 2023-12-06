//
// Created by Westly Bouchard on 12/4/23.
//

#ifndef INTERPRETER_H
#define INTERPRETER_H
#include <memory>
#include <vector>

#include "../core/ASTCommon.h"
#include "Environment.h"
#include "../expr/ExprVisitor.h"
#include "../stmt/StmtVisitor.h"


class Stmt;

class Interpreter final : public ExprVisitor<Value>, public StmtVisitor<int> {

public:
    Interpreter(std::vector<std::unique_ptr<Stmt>>& ast);

    void walk();

    void visit(const Binary& expr) override;
    void visit(const Grouping& expr) override;
    void visit(const Literal& expr) override;
    void visit(const Unary& expr) override;
    void visit(const Variable& expr) override;

    void visit(const Block& stmt) override;
    void visit(const Echo& stmt) override;
    void visit(const Exec& stmt) override;
    void visit(const Expression& stmt) override;
    void visit(const For& stmt) override;
    void visit(const If& stmt) override;
    void visit(const VarAssign& stmt) override;
    void visit(const VarDecl& stmt) override;
    void visit(const While& stmt) override;

    ~Interpreter() override = default;

private:
    Value evaluate(const std::unique_ptr<Expr>& expr);

    // static bool isTruthy(const VALUE_TYPE& value);

    // AST To walk
    std::vector<std::unique_ptr<Stmt>>& ast;

    // Global Environment
    Environment environment;
};



#endif //INTERPRETER_H
