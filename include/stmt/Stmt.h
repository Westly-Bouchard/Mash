/**
 * @file Stmt.h
 * @author Westly Bouchard (westly_bouchard@mines.edu)
 * @brief Base visitable AST node for statements
 * @version 0.1
 * @date 2023-10-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef STMT_H
#define STMT_H

#include "StmtVisitor.h"

class Expr;

class Stmt {
    public:
        virtual ~Stmt() = default;
        virtual void accept(StmtVisitor& visitor) const = 0;
};

#endif
