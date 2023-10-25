/**
 * @file Exec.h
 * @author Westly Bouchard (westly_bouchard@mines.edu)
 * @brief Visitable AST node for exec statements
 * @version 0.1
 * @date 2023-10-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef EXEC_H
#define EXEC_H

#include <memory>

#include "../expr/Expr.h"
#include "Stmt.h"

class Exec : public Stmt {
    private:
        std::unique_ptr<Expr> toRun;
        std::unique_ptr<Expr> result;

    public:
        Exec(std::unique_ptr<Expr> toRun, std::unique_ptr<Expr> result);

        std::any accept(StmtVisitor<std::any>& visitor) const override;
};

#endif
