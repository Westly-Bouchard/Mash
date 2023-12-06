//
// Created by Westly Bouchard on 12/4/23.
//

#include "../../include/core/Interpreter.h"

#include <iostream>

#include "../../include/tool/Error.hpp"

using namespace std;
using namespace TokenType;

Interpreter::Interpreter(vector<unique_ptr<Stmt>>& ast) : ast(ast) {}

void Interpreter::walk() {
    try {
        for (const auto& stmt : ast) {
            stmt->accept(*this);
        }
    } catch (mash::RuntimeError& e) {
        cerr << e.what() << endl;
    }
}

Value Interpreter::evaluate(const unique_ptr<Expr>& expr) {
    return expr->accept(*this);
}

void Interpreter::visit(const Binary& expr) {
    const Value left = expr.left->accept(*this);
    const Value right = expr.right->accept(*this);

    switch (expr.opp.type) {
        case EQUAL_EQUAL: ExprVisitor::result.set(left == right);

        case BANG_EQUAL: ExprVisitor::result.set(left != right);

        case GREATER: ExprVisitor::result.set(left > right);

        case LESS: ExprVisitor::result.set(left < right);

        case GREATER_EQUAL: ExprVisitor::result.set(left >= right);

        case LESS_EQUAL: ExprVisitor::result.set(left <= right);

        case PLUS: ExprVisitor::result = left + right;

        case MINUS: ExprVisitor::result = left - right;

        case SLASH: ExprVisitor::result = left / right;

        case STAR: ExprVisitor::result = left * right;

        default:
            break;
            //unreachable
    }

}

void Interpreter::visit(const Grouping& expr) {
    ExprVisitor::result = expr.expr->accept(*this);
}

void Interpreter::visit(const Literal& expr) {
    // Technically it's an optional but we can just unwrap it here because the parser will have ensured that it actually
    // contains a value
    auto literal = expr.value.value();

    if (holds_alternative<int>(literal)) {
        ExprVisitor::result = Value(get<int>(literal));
    } else if (holds_alternative<double>(literal)) {
        ExprVisitor::result = Value(get<double>(literal));
    } else if (holds_alternative<bool>(literal)) {
        ExprVisitor::result = Value(get<bool>(literal));
    } else if (holds_alternative<string>(literal)) {
        ExprVisitor::result = Value(get<string>(literal));
    }
}

void Interpreter::visit(const Unary& expr) {
    // Evaluate the expression to operate on
    const Value right = expr.right->accept(*this);

    // Can only negate numeric values, so only int and double
    if (expr.opp.type == MINUS) {
        if (right.isOfType(ValueType::INT)) {
            ExprVisitor::result.set(-right.getInt());
        } else if (right.isOfType(ValueType::DOUBLE)) {
            ExprVisitor::result.set(-right.getDouble());
        } else {
            throw mash::RuntimeError("Error: Attempt to negate non-numeric value");
        }
    // Can invert anything because truthiness is defined for all four mash types
    } else if (expr.opp.type == BANG) {
        ExprVisitor::result.set(!right.isTruthy());
    }
}

void Interpreter::visit(const Variable& expr) {
    ExprVisitor::result = *environment.get(expr.name);
}

void Interpreter::visit(const Block& stmt) {

}

void Interpreter::visit(const Echo& stmt) {
    cout << stmt.expr->accept(*this);
}

void Interpreter::visit(const Exec& stmt) {

}

void Interpreter::visit(const Expression& stmt) {
    stmt.expr->accept(*this);
}

void Interpreter::visit(const For& stmt) {

}

void Interpreter::visit(const If& stmt) {

}

void Interpreter::visit(const VarAssign& stmt) {
    Value newValue = stmt.expr->accept(*this);
    environment.assign(stmt.name, newValue);
}

void Interpreter::visit(const VarDecl& stmt) {
    ValueType type;
    switch (stmt.type) {
        case INT: type = ValueType::INT; break;
        case DOUBLE: type = ValueType::DOUBLE; break;
        case STRING_T: type = ValueType::STRING; break;
        case BOOLEAN: type = ValueType::BOOL; break;
        default:
            //Unreachable
            throw mash::RuntimeError("Variable declaration does not provide a valid type");
    }

    if (stmt.expr) {
        Value initializer = stmt.expr->accept(*this);

        if (initializer.isOfType(type)) {
            environment.define(stmt.name.lexeme, initializer);
        } else {
            throw mash::RuntimeError("Error: Type Mismatch, cannot create variable of provided type, initializer does not match");
        }
    } else {
        Value def(type);
        environment.define(stmt.name.lexeme, def);
    }



}

void Interpreter::visit(const While& stmt) {

}