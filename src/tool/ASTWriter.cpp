/**
 * @file ASTWriter.cpp
 * @author Westly Bouchard (westly_bouchard@mines.edu)
 * @brief implementation for writing ASTs to ostreams
 * @version 0.1
 * @date 2023-10-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "../../include/tool/ASTWriter.h"

using namespace std;
using namespace TokenType;

ASTWriter::ASTWriter(vector<unique_ptr<Stmt>>& ast, ostream& out) : out(out), ast(ast) {};

void ASTWriter::write() {
    indent = 0;
    result = "";
    
    for (const auto& stmt : ast) {
        stmt->accept(*this);
    }
}

string ASTWriter::strFromIndent() const {
    string temp = "";

    for (int i = 0; i < indent; i++) temp.push_back(' ');

    return temp;
}

void ASTWriter::visit(const Binary& expr) {
   out << strFromIndent() << "Binary Expression" << endl;

   indent += 4;

   expr.left->accept(*this);

   out << strFromIndent() << "Operator: " << expr.opp.asString() << endl;

   expr.right->accept(*this);

   indent -= 4;
}

void ASTWriter::visit(const Grouping& expr) {
    out << strFromIndent() << "Grouping Expression" << endl;

    indent += 4;

    expr.expr->accept(*this);

    indent -= 4;
}

void ASTWriter::visit(const Literal& expr) {
    switch (expr.type) {
        case Type::DOUBLE:
            out << strFromIndent() << any_cast<double>(expr.value);
            break;

        case Type::INT:
            out << strFromIndent() << any_cast<int>(expr.value);
            break;

        case Type::STRING_T:
            out << strFromIndent() << any_cast<string>(expr.value);
            break;

        // Unreachable
        default:
            break;
    }
}

void ASTWriter::visit(const Unary& expr) {
    out << strFromIndent() << expr.opp.asString();

    expr.right->accept(*this);
}

void ASTWriter::visit(const Variable& expr) {
    out << strFromIndent() << expr.name.lexeme;
}

void ASTWriter::visit(const Block& stmt) {
    out << strFromIndent() << "Block Statement" << endl;

    indent += 4;

    for (const auto& st : stmt.statements) {
        st->accept(*this);
    }

    indent -= 4;
}

void ASTWriter::visit(const Echo& stmt) {
    out << strFromIndent() << "Echo Statement" << endl;

    indent += 4;

    stmt.expr->accept(*this);

    indent -= 4;
}

void ASTWriter::visit(const Exec& stmt) {
    out << strFromIndent() << "Exec Statement" << endl;

    indent += 4;

    stmt.toRun->accept(*this);

    if (stmt.result) {
        stmt.result->accept(*this);
    }

    indent -= 4;
}

void ASTWriter::visit(const Expression& stmt) {
    out << strFromIndent() << "Expression Statement" << endl;

    indent += 4;

    stmt.expr->accept(*this);

    indent -= 4;
}

void ASTWriter::visit(const For& stmt) {
    out << strFromIndent() << "For Statement" << endl;

    indent += 4;

    out << strFromIndent() << "Condition" << endl;

    stmt.condition->accept(*this);

    out << strFromIndent() << "Statement" << endl;

    stmt.stmt->accept(*this);

    indent -= 4;
}

void ASTWriter::visit(const If& stmt) {
    out << strFromIndent() << "If Statement" << endl;

    indent += 4;

    out << strFromIndent() << "Condition" << endl;

    stmt.condition->accept(*this);

    out << strFromIndent() << "Then Branch" << endl;

    stmt.thenBranch->accept(*this);

    if (stmt.elseBranch) {
        out << strFromIndent() << "Else Branch" << endl;

        stmt.elseBranch->accept(*this);
    }

    indent -= 4;
}

void ASTWriter::visit(const VarAssign& stmt) {
    out << strFromIndent() << "Variable Assignment Statement" << endl;

    indent += 4;

    out << strFromIndent() << "Lvalue " << stmt.name.lexeme << endl;

    out << strFromIndent() << "Rvalue ";

    stmt.expr->accept(*this);

    indent -= 4;
}

void ASTWriter::visit(const VarDecl& stmt) {
    out << strFromIndent() << "Variable Declaration Statement" << endl;

    indent += 4;

    out << strFromIndent() << "Type " << TokenType::asStr(stmt.type) << endl;

    out << strFromIndent() << "Identifier " << stmt.name.lexeme << endl;

    if (stmt.expr) {
        out << strFromIndent() << "Initializer ";
        stmt.expr->accept(*this);
    }

    indent -= 4;
}

void ASTWriter::visit(const While& stmt) {
    out << strFromIndent() << "While Statement" << endl;

    indent += 4;

    out << strFromIndent() << "Condition ";

    stmt.condition->accept(*this);

    out << "Statement ";

    stmt.stmt->accept(*this);

    indent -= 4;
}