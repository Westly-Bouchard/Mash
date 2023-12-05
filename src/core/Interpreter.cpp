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

VALUE_TYPE Interpreter::evaluate(const Expr& expr) {
    expr.accept(*this);
    return result;
}

bool Interpreter::isTruthy(const VALUE_TYPE& value) {
    if (
        (holds_alternative<int>(value) && get<int>(value) == 0) ||
        (holds_alternative<double>(value) && get<double>(value) == 0) ||
        (holds_alternative<bool>(value) && !get<bool>(value))
        ) return false;

    return true;
}



void Interpreter::visit(const Binary& expr) {

}

void Interpreter::visit(const Grouping& expr) {
    result = evaluate(*expr.expr);
}

void Interpreter::visit(const Literal& expr) {
    result = expr.value.value();
}

void Interpreter::visit(const Unary& expr) {
    // Evaluate the expression to operate on
    const VALUE_TYPE right = evaluate(*expr.right);

    // Check that type is negateable, the only type in mash that is not negateable is string
    if (
        expr.opp.type == MINUS && (holds_alternative<bool>(right) || holds_alternative<string>(right))
        ) {
        throw mash::RuntimeError("Type Mismatch");
    }
    switch (expr.opp.type) {
        case MINUS: {
            if (holds_alternative<int>(right)) {
                result = -get<int>(right);
            } else if (holds_alternative<double>(right)) {
                result = -get<double>(right);
            }
        }
        break;

        case BANG: {
            result = !isTruthy(right);
        }
        break;

        default:
            //Unreachable
            break;
    }
}

void Interpreter::visit(const Variable& expr) {

}

void Interpreter::visit(const Block& stmt) {

}

void Interpreter::visit(const Echo& stmt) {

}

void Interpreter::visit(const Exec& stmt) {

}

void Interpreter::visit(const Expression& stmt) {

}

void Interpreter::visit(const For& stmt) {

}

void Interpreter::visit(const If& stmt) {

}

void Interpreter::visit(const VarAssign& stmt) {

}

void Interpreter::visit(const VarDecl& stmt) {

}

void Interpreter::visit(const While& stmt) {

}