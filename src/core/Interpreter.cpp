//
// Created by Westly Bouchard on 12/4/23.
//

#include "../../include/core/Interpreter.h"

using namespace std;

Interpreter::Interpreter(std::vector<std::unique_ptr<Stmt>>&ast) : ast(ast) {

}

void Interpreter::visit(const Binary& expr) {

}

void Interpreter::visit(const Grouping& expr) {

}

void Interpreter::visit(const Literal& expr) {

}

void Interpreter::visit(const Unary& expr) {

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