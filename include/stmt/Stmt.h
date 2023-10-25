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

#include "../util/Visitor.hpp"
#include "../util/Visitable.hpp"

class Expr;

class Stmt : public VisitableImpl<Stmt, Expr, Stmt> {};

#endif
