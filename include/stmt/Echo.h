/**
 * @file Echo.h
 * @author Westly Bouchard (westly_bouchard@mines.edu)
 * @brief Base visitable AST node for echo statements
 * @version 0.1
 * @date 2023-10-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef ECHO_H
#define ECHO_H

#include <memory>

#include "../expr/Expr.h"
#include "Stmt.h"

class Echo : public Stmt {
    private:
        std::unique_ptr<Expr> expr;

    public:
        Echo(std::unique_ptr<Expr> expr);

        void accept(StmtVisitor& visitor) const override;
};

#endif
