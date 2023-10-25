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

#include <any>

#include "StmtVisitor.h"

class Stmt {
    public:
        virtual ~Stmt() = default;
        virtual std::any accept(StmtVisitor<std::any>& visitor) const = 0;
};

#endif
