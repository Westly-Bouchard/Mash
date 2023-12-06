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

// Value Interpreter::evaluate(const Expr& expr) {
//     expr.accept(*this);
//     return move(lastResult);
// }

void Interpreter::visit(const Binary& expr) {
    // Value left = evaluate(*expr.left);
    // Value right = evaluate(*expr.right);
    //
    // // Type verification
    // switch (expr.opp.type) {
    //     case EQUAL_EQUAL: {
    //         if (left.sameTypeAs(right)) {
    //
    //         }
    //     }
    // }

}

void Interpreter::visit(const Grouping& expr) {
    // lastResult = evaluate(*expr.expr);
}

void Interpreter::visit(const Literal& expr) {
    // Technically it's an optional but we can just unwrap it here because the parser will have ensured that it actually
    // contains a value
    // auto literal = expr.value.value;
    //
    // if (holds_alternative<int>(literal)) {
    //     lastResult = Value(ValueType::INT, get<int>(literal));
    // } else if (holds_alternative<double>(literal)) {
    //     lastResult = Value(ValueType::DOUBLE, get<double>(literal));
    // } else if (holds_alternative<bool>(literal)) {
    //     lastResult = Value(ValueType::BOOL, get<bool>(literal));
    // } else if (holds_alternative<string>(literal)) {
    //     lastResult = Value(ValueType::STRING, get<string>(literal));
    // }
}

void Interpreter::visit(const Unary& expr) {
    // // Evaluate the expression to operate on
    // const Value right = evaluate(*expr.right);
    //
    // // Can only negate numeric values, so only int and double
    // if (expr.opp.type == MINUS) {
    //     if (right.isOfType(ValueType::INT)) {
    //         lastResult.set(-right.getInt());
    //     } else if (right.isOfType(ValueType::DOUBLE)) {
    //         lastResult.set(-right.getDouble());
    //     } else {
    //         throw mash::RuntimeError("Error: Attempt to negate non-numeric value");
    //     }
    // // Can invert anything because truthiness is defined for all four mash types
    // } else if (expr.opp.type == BANG) {
    //     lastResult.set(!right.isTruthy());
    // }
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