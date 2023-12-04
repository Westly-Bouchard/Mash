/**
 * @file ASTWriter.h
 * @author Westly Bouchard (westly_bouchard@mines.edu)
 * @brief A debugging tool for textual representation of abstract syntax trees
 * @version 0.1
 * @date 2023-10-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef AST_WRITER_H
#define AST_WRITER_H

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "../core/ASTCommon.h"
#include "../expr/ExprVisitor.h"
#include "../stmt/StmtVisitor.h"

class ASTWriter : public ExprVisitor, public StmtVisitor {
    public:
        /**
         * @brief Construct a new ASTWriter object
         * 
         * @param ast the AST to represent
         * @param out the ostream to write to
         */
        ASTWriter(std::vector<std::unique_ptr<Stmt>>& ast, std::ostream& out);

        /**
         * @brief Write the AST to the specified output stream
         * 
         */
        void write();

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

        ~ASTWriter() override = default;

    private:
        std::ostream& out;
        std::vector<std::unique_ptr<Stmt>>& ast;

        int indent;
        
        std::string strFromIndent() const;
};

#endif
