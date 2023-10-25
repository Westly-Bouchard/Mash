/**
 * @file ASTCommon.h
 * @author Westly Bouchard (westly_bouchard@mines.edu)
 * @brief All of the header files for the AST nodes
 * @version 0.1
 * @date 2023-10-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef AST_COMMON_H
#define AST_COMMON_H

#include "../expr/Expr.h"
#include "../expr/Binary.h"
#include "../expr/Grouping.h"
#include "../expr/Literal.h"
#include "../expr/Unary.h"
#include "../expr/Variable.h"

#include "../stmt/Stmt.h"
#include "../stmt/Block.h"
#include "../stmt/Echo.h"
#include "../stmt/Exec.h"
#include "../stmt/Expression.h"
#include "../stmt/For.h"
#include "../stmt/If.h"
#include "../stmt/VarAssign.h"
#include "../stmt/VarDecl.h"
#include "../stmt/While.h"

#endif
