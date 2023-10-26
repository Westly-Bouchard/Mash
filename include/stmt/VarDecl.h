/**
 * @file VarDecl.h
 * @author Westly Bouchard (westly_bouchard@mines.edu)
 * @brief Visitable AST node for variable declarations
 * @version 0.1
 * @date 2023-10-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef VAR_DECL_H
#define VAR_DECL_H

#include <memory>

#include "../expr/Expr.h"
#include "../core/Token.h"
#include "../core/Token.h"
#include "Stmt.h"

class VarDecl : public Stmt {
    public:
        TokenType::Type type;
        Token name;
        std::unique_ptr<Expr> expr;

        VarDecl(TokenType::Type type, Token name, std::unique_ptr<Expr> expr);

        void accept(StmtVisitor& visitor) const override;
};

#endif
