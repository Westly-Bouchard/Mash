/**
 * @file ASTWriter.cpp
 * @author Westly Bouchard (westly_bouchard@mines.edu)
 * @brief implementation for writing ASTs to out streams
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
    
    for (const auto& stmt : ast) {
        stmt->accept(*this);
    }
}

string ASTWriter::strFromIndent() const {
    string temp = "";

    for (int i = 0; i < indent; i++) temp.push_back(' ');

    return temp;
}

/*
 * Expressions will be printed inline
*/
void ASTWriter::visit(const Binary& expr) {
   out << "Binary Expression: ";

   expr.left->accept(*this);

   out << " " << expr.opp.lexeme << " ";

   expr.right->accept(*this);
}

void ASTWriter::visit(const Grouping& expr) {
    out << "Grouping Expression: ";

    expr.expr->accept(*this);
}

void ASTWriter::visit(const Literal& expr) {
    switch (expr.type) {
        case Type::DOUBLE:
            out << any_cast<double>(expr.value);
            break;

        case Type::INT:
            out << any_cast<int>(expr.value);
            break;

        case Type::STRING_T:
            out << "\"" << any_cast<string>(expr.value) << "\"";
            break;

        case Type::BOOLEAN:
            out << (any_cast<bool>(expr.value) ? "true" : "false");
            break;

        // Unreachable
        default:
            break;
    }
}

void ASTWriter::visit(const Unary& expr) {
    out << expr.opp.lexeme;

    expr.right->accept(*this);
}

void ASTWriter::visit(const Variable& expr) {
    out << "Variable Reference: " << expr.name.lexeme;
}

void ASTWriter::visit(const Block& stmt) {
    out << strFromIndent() << "Block Statement" << endl;

    indent += 4;

    for (const auto& st : stmt.statements) {
        st->accept(*this);
        out << endl;
    }

    indent -= 4;

    out << endl;
}

void ASTWriter::visit(const Echo& stmt) {
    out << strFromIndent() << "Echo Statement" << endl;

    indent += 4;

    out << strFromIndent() << "To Print: ";

    stmt.expr->accept(*this);

    indent -= 4;

    out << endl;
    out << endl;
}

void ASTWriter::visit(const Exec& stmt) {
    out << strFromIndent() << "Exec Statement" << endl;

    indent += 4;

    out << strFromIndent() << "To Run: ";

    stmt.toRun->accept(*this);

    if (stmt.result) {
        out << endl << "Store Result In: ";
        stmt.result->accept(*this);
    }

    indent -= 4;

    out << endl;
    out << endl;
}

void ASTWriter::visit(const Expression& stmt) {
    out << strFromIndent() << "Expression Statement" << endl;

    indent += 4;

    out << "Expression: ";

    stmt.expr->accept(*this);

    indent -= 4;

    out << endl;
}

void ASTWriter::visit(const For& stmt) {
    out << strFromIndent() << "For Statement" << endl;

    indent += 4;

    out << strFromIndent() << "Condition" << endl;

    indent += 4;

    out << strFromIndent();

    stmt.condition->accept(*this);

    indent -= 4;

    out << endl << strFromIndent() << "Statement" << endl;

    indent += 4;

    stmt.stmt->accept(*this);

    indent -= 4;

    indent -= 4;

    out << endl;
}

void ASTWriter::visit(const If& stmt) {
    out << strFromIndent() << "If Statement" << endl;

    indent += 4;

    out << strFromIndent() << "Condition" << endl;

    indent += 4;

    out << strFromIndent();

    stmt.condition->accept(*this);

    indent -= 4;

    out << endl << strFromIndent() << "Then Branch" << endl;

    indent += 4;

    stmt.thenBranch->accept(*this);

    indent -= 4;

    if (stmt.elseBranch) {
        out << strFromIndent() << "Else Branch" << endl;

        indent += 4;

        stmt.elseBranch->accept(*this);

        indent -= 4;
    }

    indent -= 4;

    out << endl;
}

void ASTWriter::visit(const VarAssign& stmt) {
    out << strFromIndent() << "Variable Assignment Statement" << endl;

    indent += 4;

    out << strFromIndent() << "Lvalue " << stmt.name.lexeme << endl;

    out << strFromIndent() << "Rvalue ";

    stmt.expr->accept(*this);

    indent -= 4;

    out << endl;
}

void ASTWriter::visit(const VarDecl& stmt) {
    out << strFromIndent() << "Variable Declaration Statement" << endl;

    indent += 4;

    string typeString = "";
    
    switch (stmt.type) {
        case TokenType::Type::INT: typeString = "int"; break;
        case TokenType::Type::DOUBLE: typeString = "double"; break;
        case TokenType::Type::BOOLEAN: typeString = "boolean"; break;
        case TokenType::Type::STRING_T: typeString = "string"; break;

        // Unreachable
        default: break;
    }

    out << strFromIndent() << "Type: " << typeString << endl;

    out << strFromIndent() << "Identifier: " << stmt.name.lexeme << endl;

    if (stmt.expr) {
        out << strFromIndent() << "Initializer: ";
        stmt.expr->accept(*this);
    }

    indent -= 4;

    out << endl;

    out << endl;
}

void ASTWriter::visit(const While& stmt) {
    out << strFromIndent() << "While Statement" << endl;

    indent += 4;

    out << strFromIndent() << "Condition ";

    stmt.condition->accept(*this);

    out << "Statement ";

    stmt.stmt->accept(*this);

    indent -= 4;

    out << endl;
}