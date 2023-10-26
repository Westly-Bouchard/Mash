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

ASTWriter::ASTWriter(vector<unique_ptr<Stmt>>& ast, ostream& out) : out(out), ast(ast) {};

void ASTWriter::write() {

}

void ASTWriter::visit(const Binary& expr) {
    
}

void ASTWriter::visit(const Grouping& expr) {
    
}

void ASTWriter::visit(const Literal& expr) {
    
}

void ASTWriter::visit(const Unary& expr) {
    
}

void ASTWriter::visit(const Variable& expr) {
    
}

void ASTWriter::visit(const Block& stmt) {
    
}

void ASTWriter::visit(const Echo& stmt) {
    
}

void ASTWriter::visit(const Exec& stmt) {
    
}

void ASTWriter::visit(const Expression& stmt) {
    
}

void ASTWriter::visit(const For& stmt) {
    
}

void ASTWriter::visit(const If& stmt) {
    
}

void ASTWriter::visit(const VarAssign& stmt) {
    
}

void ASTWriter::visit(const VarDecl& stmt) {
    
}

void ASTWriter::visit(const While& stmt) {
    
}