/**
 * @file Block.cpp
 * @author Westly Bouchard (westly_bouchard@mines.edu)
 * @brief Implementation for block AST nodes
 * @version 0.1
 * @date 2023-10-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "../../include/stmt/Block.h"

Block::Block(std::vector<std::unique_ptr<Stmt>> statements) : statements(std::move(statements)) {}

void Block::accept(StmtVisitor& visitor) const {
    visitor.visit(*this);
}
