/**
 * @file Expr.h
 * @author Westly Bouchard (westly_bouchard@mines.edu)
 * @brief Base visitable class for expression AST nodes
 * @version 0.1
 * @date 2023-10-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef EXPR_H
#define EXPR_H

#include <any>

#include "../util/Visitable.hpp"
#include "../util/Visitor.hpp"

#include "../stmt/Stmt.h"

class Expr : public VisitableImpl<Expr, Expr, Stmt> {};

#endif
