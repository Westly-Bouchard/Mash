/**
 * @file Echo.cpp
 * @author Westly Bouchard (westly_bouchard@mines.edu)
 * @brief Implementation for echo AST nodes
 * @version 0.1
 * @date 2023-10-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "../../include/stmt/Echo.h"

Echo::Echo(std::unique_ptr<Expr> expr) : expr(std::move(expr)) {}
