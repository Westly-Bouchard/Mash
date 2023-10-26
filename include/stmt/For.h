/**
 * @file For.h
 * @author Westly Bouchard (westly_bouchard@mines.edu)
 * @brief Visitable AST node for for statements
 * @version 0.1
 * @date 2023-10-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef FOR_H
#define FOR_H

#include <memory>

#include "../expr/Expr.h"
#include "Stmt.h"

class For : public Stmt {
    public:
        std::unique_ptr<Expr> condition;
        std::unique_ptr<Stmt> stmt;

        For(std::unique_ptr<Expr> condition, std::unique_ptr<Stmt> stmt);

        void accept(StmtVisitor& visitor) const override;
};

#endif
