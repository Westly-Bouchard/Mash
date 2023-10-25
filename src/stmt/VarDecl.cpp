/**
 * @file VarDecl.cpp
 * @author Westly Bouchard (westly_bouchard@mines.edu)
 * @brief Implementation for variable declaration AST nodes
 * @version 0.1
 * @date 2023-10-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "../../include/stmt/VarDecl.h"

VarDecl::VarDecl(TokenType::Type type, Token name, std::unique_ptr<Expr> expr) :
                   type(type), name(name), expr(std::move(expr)) {}
