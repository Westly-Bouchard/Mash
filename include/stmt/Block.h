/**
 * @file Block.h
 * @author Westly Bouchard (westly_bouchard@mines.edu)
 * @brief Visitable AST node for block statements
 * @version 0.1
 * @date 2023-10-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef BLOCK_H
#define BLOCK_H

#include <memory>
#include <vector>

#include "Stmt.h"

class Block : public Stmt {
    private:
        std::vector<std::unique_ptr<Stmt>> statements;

    public:
        Block(std::vector<std::unique_ptr<Stmt>> statements);

};

#endif
